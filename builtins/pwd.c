/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:19:18 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 14:02:42 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envctl.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	pwd_cmd(char **cmd_args, t_hashtable env)
{
	char	*wd1;
	char	*wd2;

	wd1 = lookup_env_var_value("PWD", env);
	wd2 = getcwd(NULL, 0);
	if (!wd1 && !wd2)
	{
		perror("builtin: pwd");
		return (1);
	}
	if (wd2)
		ft_putendl_fd(wd2, STDOUT_FILENO);
	else
		ft_putendl_fd(wd1, STDOUT_FILENO);
	free(wd2);
	return (0);
	do_nothing_builtins(cmd_args, env);
}
