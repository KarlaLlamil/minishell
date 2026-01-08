/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 02:08:23 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 02:08:35 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "expansion.h"
#include "envctl.h"
#include <stdlib.h>

static int	set_expander_values(t_expansion *expander, t_hashtable env)
{
	size_t	len;

	expander->expand = true;
	expander->end_name = expander->name + 1;
	if (*(expander->end_name) == '?')
		++(expander->end_name);
	else
		is_valid_name(&expander->end_name);
	expander->next = ft_strchr(expander->name + 1, '$');
	len = (expander->end_name - expander->name) - 1;
	if ((expander->name + 1) == expander->end_name)
		expander->expand = false;
	else
	{
		expander->name = ft_substr(expander->name, 1, len);
		if (expander->name == NULL)
			return (1);
		expander->value = lookup_env_var_value(expander->name, env);
		free (expander->name);
		expander->expand = true;
		expander->name = NULL;
	}
	return (0);
}

int	substitute_var_here_doc(char	**line, t_hashtable env)
{
	char		*expanded;
	t_expansion	expander;

	expander = (t_expansion){};
	expander.name = ft_strchr(*line, '$');
	expander.status = 0;
	expanded = ft_substr(*line, 0, expander.name - *line);
	if (expanded == NULL)
		return (1);
	while (expander.name != NULL && expander.status == 0)
	{
		expander.status = set_expander_values(&expander, env);
		if (expander.value == NULL && expander.expand == true)
			expander.status = value_null(expanded, &expander);
		else if (expander.value != NULL && expander.expand == true)
			expander.status = value_not_null(expanded, &expander);
		else
			expander.status = not_expandable_var(expanded, &expander);
		free(expanded);
		expanded = expander.line;
		expander.name = expander.next;
	}
	free(*line);
	*line = expander.line;
	return (expander.status);
}
