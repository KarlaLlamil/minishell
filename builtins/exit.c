/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 05:49:54 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 14:26:10 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "signaling.h"
#include "libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>

static int	count_args(char **cmd_args)
{
	int	n_args;

	n_args = 0;
	while (cmd_args[n_args] != NULL)
		n_args++;
	return (n_args);
}

static int	is_number(char *s)
{
	while (s && *s)
	{
		if (!ft_isdigit(*s) && *s != '+' && *s != '-')
			return (0);
		s++;
	}
	return (1);
}

int	exit_cmd(char **cmd_args, t_hashtable env)
{
	int		exit_status;
	int		n_args;
	char	*es_str;

	n_args = count_args(cmd_args);
	exit_status = 1;
	es_str = lookup_env_var_value("?", env);
	if (n_args > 2)
		return (ft_putendl_fd("builtins: exit: too many arguments",
				STDERR_FILENO), 1);
	if (n_args == 2 && !is_number(cmd_args[1]))
	{
		ft_putendl_fd("builtins: exit: numeric argument required",
			STDERR_FILENO);
		exit_status = 2;
	}
	else if (n_args == 2)
		exit_status = ft_atoi(cmd_args[1]);
	else if (es_str)
		exit_status = ft_atoi(es_str);
	rl_clear_history();
	clear_env(env);
	exit(exit_status);
	return (1);
}
