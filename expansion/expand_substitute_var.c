/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_substitute_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 02:06:10 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 17:12:16 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "expansion.h"
#include "envctl.h"

int	not_expandable_var(char *expanded, t_expansion *expander)
{
	char	*not_expandable;
	size_t	len;

	len = expander->next - expander->name;
	if (expander->next != NULL)
	{
		not_expandable = ft_substr(expander->name, 0, len);
		if (not_expandable == NULL)
			return (1);
		expander->line = ft_strjoin(expanded, not_expandable);
		free(not_expandable);
	}
	else
		expander->line = ft_strjoin(expanded, expander->name);
	if (expander->line == NULL)
		return (1);
	return (0);
}

int	value_null( char *expanded, t_expansion *expander)
{
	char	*not_expandable;
	size_t	len;

	len = expander->next - expander->end_name;
	if (*expander->end_name == '\0')
		expander->line = ft_strdup(expanded);
	else
	{
		if (expander->next != NULL && expander->end_name != expander->next)
		{
			not_expandable = ft_substr(expander->end_name, 0, len);
			if (not_expandable == NULL)
				return (1);
			expander->line = ft_strjoin(expanded, not_expandable);
			free (not_expandable);
		}
		else if (expander->next == NULL)
			expander->line = ft_strjoin(expanded, expander->end_name);
		else if (expander->end_name == expander->next)
			expander->line = ft_strdup(expanded);
	}
	if (expander->line == NULL)
		return (1);
	return (0);
}

int	value_not_null( char *expanded, t_expansion *expander)
{
	char	*not_expandable;
	size_t	len;

	len = expander->next - expander->end_name;
	if (*expander->end_name == '\0' || expander->end_name == expander->next)
		expander->line = ft_strjoin(expanded, expander->value);
	else
	{
		if (expander->next != NULL)
			not_expandable = ft_substr(expander->end_name, 0, len);
		else
			not_expandable = ft_strdup(expander->end_name);
		if (not_expandable == NULL)
			return (1);
		expander->value = ft_strjoin(expander->value, not_expandable);
		if (expander->value == NULL)
			return (free(not_expandable), 1);
		expander->line = ft_strjoin(expanded, expander->value);
		free(not_expandable);
		free (expander->value);
	}
	if (expander->line == NULL)
		return (1);
	return (0);
}

static int	set_values_exp_cmd(t_expansion *expander, t_hashtable env)
{
	int	len;

	expander->end_name = expander->name + 1;
	if (*(expander->end_name) == '?')
		++(expander->end_name);
	else
		is_valid_name(&expander->end_name);
	expander->next = ft_strchr(expander->name + 1, '$');
	is_expandable(expander);
	if ((expander->name + 1) == expander->end_name)
		expander->expand = false;
	if (expander->expand == true)
	{
		len = (expander->end_name - expander->name) - 1;
		expander->name = ft_substr(expander->name, 1, len);
		if (expander->name == NULL)
			return (1);
		expander->value = lookup_env_var_value(expander->name, env);
		free (expander->name);
		expander->name = NULL;
	}
	return (0);
}

int	substitute_var_cmds(char	*arg, t_expansion *expander, t_hashtable env)
{
	char	*expanded;

	expanded = ft_substr(arg, 0, expander->name - arg);
	if (expanded == NULL)
		return (1);
	expander->end_name = expander->name;
	while (expander->name != NULL && expander->status == 0)
	{
		expander->status = set_values_exp_cmd(expander, env);
		if (expander->status == 0 && expander->expand == false)
			expander->status = not_expandable_var(expanded, expander);
		else if (expander->status == 0 && expander->expand == true)
		{
			if (expander->value == NULL)
				expander->status = value_null(expanded, expander);
			else
				expander->status = value_not_null(expanded, expander);
		}
		free(expanded);
		expanded = expander->line;
		expander->name = expander->next;
	}
	return (expander->status);
}
