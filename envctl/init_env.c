/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:26:14 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 04:05:49 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	handle_errors_init_env(int err, t_hashtable env)
{
	if (err == 0)
		return ;
	if (err == 1)
		perror("init_env: enviroment could not be imported correctly");
	if (err == 2)
		ft_putendl_fd(
			"init_env: imported environment was not properly formatted",
			STDERR_FILENO);
	clear_env(env);
}

/**
 * @brief Sets variable SHLVL to be 1 more than the previous shell
 * @return 0 if success, 1 if error (alloc)
 */
static int	increase_shlvl(t_hashtable env)
{
	t_envvar	*shlvl;
	char		*curr_lvl;
	int			err;

	err = 0;
	shlvl = lookup_env_var("SHLVL", env);
	if (shlvl && shlvl->value)
		curr_lvl = ft_itoa(ft_atoi(shlvl->value) + 1);
	else
		curr_lvl = ft_itoa(1);
	if (!curr_lvl)
		err = 1;
	err = err || set_env_var("SHLVL", curr_lvl, true, env);
	free(curr_lvl);
	return (err);
}

static int	import_variable(t_hashtable env, char *var_str, char *eq_ptr)
{
	char	*name;
	char	*value;
	int		err;

	err = 0;
	name = ft_substr(var_str, 0, eq_ptr - var_str);
	value = ft_strdup(eq_ptr + 1);
	if (!name || !value || set_env_var(name, value, true, env))
		err = 1;
	free(name);
	free(value);
	return (err);
}

int	init_env(t_hashtable env, char **env_import)
{
	char	*eq_ptr;
	int		err;

	err = 0;
	ft_bzero(env, sizeof(t_hashtable));
	while (env_import && *env_import && !err)
	{
		eq_ptr = ft_strchr(*env_import, '=');
		if (eq_ptr)
			err = import_variable(env, *env_import, eq_ptr);
		else
			err = 2;
		env_import++;
	}
	err = err || set_exit_status_var(0, env);
	err = err || increase_shlvl(env);
	handle_errors_init_env(err, env);
	unset_env_var("_", env);
	return (err);
}

int	init_env_with_environ(t_hashtable env)
{
	extern char	**environ;

	return (init_env(env, environ));
}
