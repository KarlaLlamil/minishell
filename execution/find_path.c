/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:27:18 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 11:42:56 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "./utils/utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

static char	*file_path_cpy(char *file_name)
{
	char	*file_path;

	file_path = ft_strdup(file_name);
	if (!file_path)
		perror("minishell: error interpreting cmd path");
	return (file_path);
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

static int	is_exe(char *path)
{
	struct stat	file;

	if (access(path, X_OK))
		return (0);
	stat(path, &file);
	if (S_ISREG(file.st_mode))
		return (1);
	return (0);
}

static char	**split_the_path(t_hashtable env)
{
	char	**path_var;

	if (lookup_env_var_value("PATH", env))
		path_var = strict_split(lookup_env_var_value("PATH", env), ':');
	else
		path_var = strict_split("", ':');
	if (!path_var)
		perror("minishell: error interpreting cmd path");
	return (path_var);
}

char	*find_path(char *file_name, t_hashtable env)
{
	char	**path_var;
	char	*file_path;
	size_t	tmp;

	if (ft_strchr(file_name, '/'))
		return (file_path_cpy(file_name));
	path_var = split_the_path(env);
	file_path = NULL;
	tmp = 0;
	while (path_var && path_var[tmp])
	{
		file_path = path_join(path_var[tmp], file_name);
		if (!file_path)
			perror("minishell: error interpreting cmd path");
		if (!file_path || is_exe(file_path))
			break ;
		free(file_path);
		file_path = NULL;
		tmp++;
	}
	free_arr(&path_var);
	return (file_path);
}
