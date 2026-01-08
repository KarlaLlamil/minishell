/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:41:00 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 01:50:04 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "tokens.h"
#include "utilities_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"

bool	is_valid_name(char **str)
{
	if (ft_isalpha(**str) == 0 && **str != '_')
		return (false);
	++(*str);
	while (**str)
	{
		if (**str == '=')
			return (true);
		else if (ft_isalnum(**str) == 0 && **str != '_')
			return (false);
		++(*str);
	}
	return (true);
}

bool	is_assigmnt(char	*str)
{
	if (is_valid_name(&str) && *str == '=')
		return (true);
	return (false);
}

static bool	fill_assignment(t_assignment *new, t_parser *parser, bool export)
{
	new->export_env = export;
	new->name = ft_strdup(parser->tokens[parser->indx]->value);
	if (new->name == NULL)
	{
		parser->status = ERR_ALLOC;
		free(new);
		return (false);
	}
	new->value = ft_strchr(new->name, '=');
	*new->value = '\0';
	new->value = ft_strdup(new->value + 1);
	++parser->indx;
	if (new->value == NULL)
	{
		parser->status = ERR_ALLOC;
		free(new->name);
		free(new);
		return (false);
	}
	return (true);
}

void	add_assignment(t_list **assignment, t_parser *parser, bool export)
{
	t_assignment	*new_assignment;
	t_list			*new_node;

	new_assignment = malloc(sizeof(t_assignment));
	if (new_assignment == NULL)
	{
		parser->status = ERR_ALLOC;
		return ;
	}
	if (fill_assignment(new_assignment, parser, export) == false)
		return ;
	new_node = ft_lstnew(new_assignment);
	ft_lstadd_back(assignment, new_node);
}

t_ast_node	*cmd_just_assignments(t_parser *parser)
{
	t_list		*assignments;
	t_ast_node	*node;

	assignments = NULL;
	node = NULL;
	while (parser->tokens[parser->indx] != NULL && parser->status == OK
		&& parser->tokens[parser->indx]->type == TOKEN_WORD)
	{
		if (is_assigmnt(parser->tokens[parser->indx]->value) == true)
			add_assignment(&assignments, parser, false);
		else
			break ;
	}
	if (parser->status == ERR_ALLOC)
	{
		ft_lstclear(&assignments, del_asgmnt);
		return (NULL);
	}
	node = make_astnode(AST_ASSIGNMENT, parser);
	if (node != NULL)
		node->data = assignments;
	return (node);
}
