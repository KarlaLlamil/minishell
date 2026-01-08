/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_nothing_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:54:39 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 13:59:26 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

void	do_nothing_builtins(char **cmd_args, t_hashtable env)
{
	t_list	**env2;
	char	**cmd_args2;

	env = NULL;
	env2 = env;
	cmd_args = NULL;
	cmd_args2 = cmd_args;
}
