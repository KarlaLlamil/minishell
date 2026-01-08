/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:37:06 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 16:38:09 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envctl.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static int	print_export_env(t_hashtable env)
{
	char	**env_arr;
	size_t	i;

	env_arr = meta_export(env);
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
}

static bool	is_valid(char *str)
{
	if (ft_isalpha(*str) == 0 && *str != '_')
		return (false);
	++str;
	while (*str)
	{
		if (*str == '=')
			return (true);
		else if (ft_isalnum(*str) == 0 && *str != '_')
			return (false);
		++str;
	}
	return (true);
}

static int	check_valid_name(char *name)
{
	if (!is_valid(name))
	{
		ft_putstr_fd("builtins: export: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	get_name_and_value(char *str, char **name, char **value)
{
	char	*ptr;

	ptr = ft_strchr(str, '=');
	if (ptr)
	{
		*name = ft_substr(str, 0, ptr - str);
		*value = ft_strdup(ptr + 1);
	}
	else
	{
		*name = ft_strdup(str);
		*value = NULL;
	}
	if (!(*name) || (ptr && !(*value)))
		return (1);
	return (0);
}

int	export_cmd(char **cmd_args, t_hashtable env)
{
	char	*name;
	char	*value;
	int		err;

	err = 0;
	if (!*(++cmd_args))
		return (print_export_env(env));
	while (*cmd_args && err != 1)
	{
		if (!check_valid_name(*cmd_args))
		{
			if (get_name_and_value(*cmd_args, &name, &value)
				|| set_env_var(name, value, true, env))
			{
				perror("builtins: export");
				err = 1;
			}
			free(name);
			free(value);
		}
		else
			err = 2;
		cmd_args++;
	}
	return ((err != 0));
}
