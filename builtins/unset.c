/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:33:20 by crirodr2          #+#    #+#             */
/*   Updated: 2025/10/23 18:41:30 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"

int	unset_cmd(char **cmd_args, t_hashtable env)
{
	while (*cmd_args)
	{
		unset_env_var(*cmd_args, env);
		cmd_args++;
	}
	return (0);
}
