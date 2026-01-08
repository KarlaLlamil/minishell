/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tmp_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 02:55:46 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 02:17:59 by crirodr2         ###   ########.fr       */
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

static int	create_tmp_var(char *name, char *value, t_hashtable env)
{
	t_envvar	*var;
	t_list		*var_lst;

	var = (t_envvar *)ft_calloc(1, sizeof(t_envvar));
	if (!var)
		return (1);
	var->name = ft_strdup(name);
	var->value = NULL;
	if (value)
		var->value = ft_strdup(value);
	var->export_env = true;
	var_lst = ft_lstnew(var);
	if (!var->name || (value && !var->value) || !var_lst)
	{
		free_everything(var, var_lst);
		return (1);
	}
	ft_lstadd_front(&(env[TMP_VAR]), var_lst);
	return (0);
}

/**
 * @brief Set variable to temp enviroment
 * @param name: variable name
 * @param value: variable value or NULL.
 * @param env: enviroment to store the variable to
 * @return 0 if success, 1 if error (alloc), 2 if wrong use (no name)
 */
int	set_tmp_var(char *name, char *value, t_hashtable env)
{
	t_envvar	*var;

	if (!name)
		return (2);
	var = lookup_tmp_var(name, env);
	if (var)
	{
		if (value)
		{
			free(var->value);
			var->value = ft_strdup(value);
			if (!var->value)
				return (1);
		}
		var->export_env = true;
	}
	else
		return (create_tmp_var(name, value, env));
	return (0);
}
