/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:45:00 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 14:13:00 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int	count_args(char **cmd_args)
{
	int	n_args;

	n_args = 0;
	while (cmd_args[n_args] != NULL)
		n_args++;
	return (n_args);
}

static char	*path_join(char *root, char *branch)
{
	char	*path;
	size_t	len_root;
	size_t	len_branch;

	len_root = ft_strlen(root);
	len_branch = ft_strlen(branch);
	if (len_root == 0)
		path = ft_strdup(branch);
	else
		path = ft_calloc(len_root + len_branch + 2, sizeof(char));
	if (!path)
		return (NULL);
	if (len_root == 0)
		return (path);
	ft_strlcpy(path, root, len_root + 1);
	path[len_root] = '/';
	ft_strlcat(path, branch, len_branch + len_root + 2);
	return (path);
}

static void	set_pwd_vars(char *path, t_hashtable env)
{
	char	*pwd;

	set_env_var("OLDPWD", lookup_env_var_value("PWD", env), true, env);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("builtins: cd: error retrieving current directory: getcwd");
		if (path[0] != '.')
			pwd = ft_strdup(path);
		else
			pwd = path_join(lookup_env_var_value("OLDPWD", env), path);
	}
	if (set_env_var("PWD", pwd, true, env) || !pwd)
		perror("builtins: cd: error setting PWD");
	free(pwd);
}

int	cd_cmd(char **cmd_args, t_hashtable env)
{
	char	*path;
	int		n_args;

	n_args = count_args(cmd_args);
	if (n_args > 2)
		return (ft_putendl_fd("builtins: cd: too many arguments",
				STDERR_FILENO), 1);
	if (n_args < 2)
		path = lookup_env_var_value("HOME", env);
	else
		path = cmd_args[1];
	if (!path)
		return (ft_putendl_fd("builtins: cd: HOME not set", STDERR_FILENO), 1);
	if (chdir(path))
		return (perror("builtins: cd"), 1);
	set_pwd_vars(path, env);
	return (0);
}
