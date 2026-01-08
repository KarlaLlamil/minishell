/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:23:48 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 16:38:19 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envctl.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	env_cmd(char **cmd_args, t_hashtable env)
{
	char	**env_arr;
	size_t	i;

	env_arr = export_env(env);
	if (!env_arr)
	{
		perror(
			"minishell: env: export_env: no enviroment export array generated");
		return (1);
	}
	i = 0;
	while (env_arr[i] != NULL)
	{
		ft_putendl_fd(env_arr[i], STDOUT_FILENO);
		free(env_arr[i]);
		i++;
	}
	free(env_arr);
	return (0);
	do_nothing_builtins(cmd_args, env);
}
