/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 04:08:39 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 04:14:40 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "expansion.h"

void	remove_quotes(char *str, t_expansion *expander)
{
	int		len;

	if (expander->in_quotes == false)
		return ;
	len = ft_strlen(expander->start_quotes);
	ft_memmove(expander->start_quotes, expander->start_quotes + 1, len);
	expander->end_quotes = expander->end_quotes - 1;
	len = ft_strlen(expander->end_quotes);
	ft_memmove(expander->end_quotes, expander->end_quotes + 1, len);
	expander->start_quotes = str;
	while (expander->start_quotes != NULL)
	{
		if (expander->type == SINGEL)
			expander->start_quotes = ft_strchr(str, '\'');
		else if (expander->type == DOUBLE)
			expander->start_quotes = ft_strchr(str, '\"');
		if (expander->start_quotes != NULL)
		{
			len = ft_strlen(expander->start_quotes);
			ft_memmove(expander->start_quotes, expander->start_quotes + 1, len);
		}
	}
}

void	is_quoted(char	*arg, t_expansion *expander)
{
	char		*d_quote;

	expander->start_quotes = ft_strchr(arg, '\'');
	expander->end_quotes = ft_strrchr(arg, '\'');
	d_quote = ft_strchr(arg, '\"');
	if (expander->start_quotes || d_quote)
	{
		expander->in_quotes = true;
		expander->type = SINGEL;
		if (expander->start_quotes == NULL
			|| (d_quote != NULL && d_quote < expander->start_quotes))
		{
			expander->start_quotes = d_quote;
			expander->end_quotes = ft_strrchr(arg, '\"');
			expander->type = DOUBLE;
		}
	}
}

void	is_expandable( t_expansion *expander)
{
	expander->expand = false;
	if (expander->name == NULL)
	{
		expander->expand = false;
		return ;
	}
	if (expander->start_quotes == NULL || *expander->start_quotes == '\"')
	{
		expander->expand = true;
		return ;
	}
	if (expander->name < expander->start_quotes
		|| expander->name > expander->end_quotes)
	{
		expander->expand = true;
		return ;
	}
	else
		expander->expand = false;
}
