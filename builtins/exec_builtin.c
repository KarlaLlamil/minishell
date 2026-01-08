/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:07:12 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 13:50:31 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_builtin(char **cmd_args, t_hashtable env)
{
	int					exit_status;
	t_builtin_type		bin_i;
	const t_builtin_cmd	builtins[] = {
		&echo_cmd,
		&cd_cmd,
		&pwd_cmd,
		&export_cmd,
		&unset_cmd,
		&env_cmd,
		&exit_cmd,
		NULL
	};

	bin_i = which_builtin(cmd_args[0]);
	if (bin_i != NOT_BUILTIN)
		exit_status = builtins[bin_i](cmd_args, env);
	else
		exit_status = 1;
	return (exit_status);
}
