/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 03:55:00 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 04:10:57 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include <stdlib.h>

static void	free_everything(t_envvar *var, t_list	*var_lst)
{
	free(var->name);
	free(var->value);
	free(var);
	free(var_lst);
}

static int	create_exit_status_var(int value, t_hashtable env)
{
	const char	*name = "?";
	t_envvar	*var;
	t_list		*var_lst;

	var = (t_envvar *)ft_calloc(1, sizeof(t_envvar));
	if (!var)
		return (1);
	var->name = ft_strdup(name);
	var->value = ft_itoa(value);
	var->export_env = false;
	var_lst = ft_lstnew(var);
	if (!var->name || !var->value || !var_lst)
	{
		free_everything(var, var_lst);
		return (1);
	}
	ft_lstadd_front(&(env[EXITSTAT_VAR]), var_lst);
	return (0);
}

/**
 * @brief Store exit status in enviroment
 * @return 0 if success, 1 if error (alloc)
 */
int	set_exit_status_var(int value, t_hashtable env)
{
	const char	*name = "?";
	t_envvar	*var;

	var = lookup_env_var((char *)name, env);
	if (var)
	{
		free(var->value);
		var->value = ft_itoa(value);
		if (!var->value)
			return (1);
	}
	else
		return (create_exit_status_var(value, env));
	return (0);
}
