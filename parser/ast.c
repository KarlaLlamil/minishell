/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:42:05 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 13:54:52 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "tokens.h"
#include "execution.h"
#include "libft.h"
#include "utilities_parser.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "envctl.h"
#include "signaling.h"

static t_ast_node	*search_root(t_ast_node *node)
{
	while (node->root != NULL)
		node = node->root;
	return (node);
}

void	destroy_ast(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->root != NULL)
		node = search_root(node);
	destroy_node(node);
}

void	ast_handle_error(t_ast_node *node, t_parser *parser)
{
	if (node != NULL)
		node = search_root(node);
	destroy_ast(node);
	if (parser->status == ERR_ALLOC)
		perror("Error allocating memory");
	if (parser->status == MISSING_FILE)
		ft_putendl_fd ("minishell: syntax error near \
unexpected token redirection", 2);
	else if (parser->status == INCOMPLETE_PIPE)
		ft_putendl_fd ("minishell: syntax error near unxpected token '|'", 2);
	else if (parser->status == INCOMPLETE_AND)
		ft_putendl_fd ("minishell: syntax error near unexpected token '&&'", 2);
	else if (parser->status == INCOMPLETE_OR)
		ft_putendl_fd ("minishell: syntax error near unxpected token '||'", 2);
	else if (parser->status == MISSING_PARENTHESES)
		ft_putendl_fd ("minishell: syntax error near unxpected \
token near '()'", 2);
}

int	make_ast(t_token **tokens, t_hashtable env)
{
	t_ast_node	*root;
	t_parser	parser;

	parser = (t_parser){};
	parser.tokens = tokens;
	root = parse_compoud_cmd(&parser);
	lexer_destroy_tokens(tokens);
	if (parser.status != OK)
	{
		ast_handle_error(root, &parser);
		return (1);
	}
	else if (parser.here_doc == true)
	{
		if (search_heredoc(root, true, env) == false || g_sigstat == SIG_SIGINT)
		{
			destroy_ast(root);
			return (1);
		}
	}
	store_ast(root, env);
	return (0);
}
