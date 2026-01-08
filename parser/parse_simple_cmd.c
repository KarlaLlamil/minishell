/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:40 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 02:03:47 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utilities_parser.h"
#include "tokens.h"
#include "envctl.h"
#include <stdlib.h>
#include "libft.h"

int	count_args(t_token **tokens, int indx)
{
	int	num;

	num = 0;
	while (tokens[indx] != NULL )
	{
		if (tokens[indx]->type == TOKEN_WORD
			&& (is_assigmnt(tokens[indx]->value) == false || num > 0))
		{
			++num;
			++indx;
		}
		else if (tokens[indx]->type == TOKEN_WORD
			&& is_assigmnt(tokens[indx]->value) == true && num == 0)
			++indx;
		else if (is_redir(tokens[indx]->type))
		{
			if (tokens[indx + 1] != NULL)
				indx = indx + 2;
			else
				++indx;
		}
		else
			return (num);
	}
	return (num);
}

static t_command	*init_cmd(int n, t_parser *parser)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (parser->status = ERR_ALLOC, NULL);
	cmd->n_args = n;
	if (n == 0)
		cmd->arguments = NULL;
	else
	{
		cmd->arguments = malloc(sizeof (char *) * (cmd->n_args + 1));
		if (cmd->arguments == NULL)
		{
			parser->status = ERR_ALLOC;
			return (NULL);
		}
		while (n >= 0)
		{
			cmd->arguments[n] = NULL;
			--n;
		}
	}
	cmd->redirs = NULL;
	cmd->assignments = NULL;
	return (cmd);
}

static void	fill_command(t_command *cmd, t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->tokens[parser->indx] != NULL && parser->status == OK)
	{
		if ((i > 0 || is_assigmnt(parser->tokens[parser->indx]->value) == false)
			&& parser->tokens[parser->indx]->type == TOKEN_WORD)
		{
			cmd->arguments[i] = ft_strdup(parser->tokens[parser->indx]->value);
			if (cmd->arguments[i] == NULL)
				parser->status = ERR_ALLOC;
			++i;
			++parser->indx;
		}
		else if (parser->tokens[parser->indx]->type == TOKEN_WORD && i == 0
			&& is_assigmnt(parser->tokens[parser->indx]->value) == true)
			add_assignment(&cmd->assignments, parser, true);
		else if (is_redir(parser->tokens[parser->indx]->type))
			add_redir(&cmd->redirs, parser);
		else
			break ;
	}
}

static t_command	*make_command(int n, t_parser *parser)
{
	t_command	*cmd;

	cmd = init_cmd(n, parser);
	if (parser->status == ERR_ALLOC)
		return (NULL);
	fill_command(cmd, parser);
	if (parser->status == ERR_ALLOC)
	{
		del_args(cmd->arguments);
		ft_lstclear(&cmd->assignments, del_asgmnt);
		ft_lstclear(&cmd->redirs, del_reddir);
		free(cmd);
		return (NULL);
	}
	else
		return (cmd);
}

t_ast_node	*parse_simple_cmd(t_parser *parser)
{
	t_ast_node	*node;
	t_command	*cmd;
	int			n;

	node = NULL;
	if (parser->status != OK || parser->tokens[parser->indx] == NULL)
		return (NULL);
	n = count_args(parser->tokens, parser->indx);
	if (n != 0 || is_redir(parser->tokens[parser->indx]->type))
	{
		cmd = make_command(n, parser);
		if (cmd == NULL)
			return (NULL);
		node = make_astnode(AST_SIMPLE_CMD, parser);
		if (node != NULL)
			node->data = cmd;
	}
	else if (n == 0 && parser->tokens[parser->indx] != NULL
		&& parser->tokens[parser->indx]->type == TOKEN_WORD)
		node = cmd_just_assignments(parser);
	else
		return (NULL);
	return (node);
}
