/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_generator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:47 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 07:16:25 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utilities_parser.h"
#include <stdlib.h>

t_ast_node	*make_astnode( t_node_type type, t_parser *parser)
{
	t_ast_node	*new;

	new = malloc(sizeof(t_ast_node));
	if (new == NULL)
		return (parser->status = ERR_ALLOC, NULL);
	new->type = type;
	if (new->type != AST_SIMPLE_CMD && new->type != AST_ASSIGNMENT)
		++parser->indx;
	new->data = NULL;
	new->left = NULL;
	new->right = NULL;
	new->root = NULL;
	return (new);
}

static t_ast_node	*parse_cmd(t_parser *parser)
{
	t_ast_node	*node;

	node = NULL;
	if (parser->status != OK || parser->tokens[parser->indx] == NULL)
		return (NULL);
	if (parser->tokens[parser->indx]->type == TOKEN_L_PAREN)
	{
		if (parser->tokens[parser->indx + 1]->type == TOKEN_R_PAREN)
		{
			parser->status = MISSING_PARENTHESES;
			return (NULL);
		}
		node = make_astnode(AST_PARENTHESES, parser);
		if (parser->status == ERR_ALLOC)
			return (NULL);
		node->left = parse_compoud_cmd(parser);
		if (parser->status == ERR_ALLOC)
			return (node);
		if (parser->tokens[parser->indx]->type == TOKEN_R_PAREN)
			++parser->indx;
		node->left->root = node;
	}
	else
		node = parse_simple_cmd(parser);
	return (node);
}

static t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_ast_node	*left_node;
	t_ast_node	*root;

	if (parser->status != OK || parser->tokens[parser->indx] == NULL)
		return (NULL);
	root = parse_cmd(parser);
	while (parser->tokens[parser->indx] != NULL
		&& parser->tokens[parser->indx]->type == TOKEN_PIPE
		&& parser->status == OK)
	{
		left_node = root;
		root = make_astnode(AST_PIPE, parser);
		if (parser->status == ERR_ALLOC)
			return (left_node);
		root->left = left_node;
		root->right = parse_cmd(parser);
		if ((root->right == NULL || root->left == NULL) && parser->status == OK)
			parser->status = INCOMPLETE_PIPE;
		if (left_node != NULL)
			root->left->root = root;
		if (root->right != NULL)
			root->right->root = root;
	}
	return (root);
}

static void	node_compound_cmd(t_ast_node *root, t_parser *parser)
{
	if (root->left == NULL || root->right == NULL)
	{
		if (parser->status == OK && root->type == AST_AND)
			parser->status = INCOMPLETE_AND;
		else if (parser->status == OK && root->type == AST_OR)
			parser->status = INCOMPLETE_OR;
	}
	if (root->left != NULL)
		root->left->root = root;
	if (root->right != NULL)
		root->right->root = root;
}

t_ast_node	*parse_compoud_cmd(t_parser *parser)
{
	t_ast_node	*left_node;
	t_ast_node	*root;

	if (parser->status != OK || parser->tokens[parser->indx] == NULL)
		return (NULL);
	root = parse_pipeline(parser);
	while (parser->tokens[parser->indx] != NULL && parser->status == OK
		&& (parser->tokens[parser->indx]->type == TOKEN_AND_IF
			|| parser->tokens[parser->indx]->type == TOKEN_OR_IF))
	{
		left_node = root;
		if (parser->tokens[parser->indx]->type == TOKEN_AND_IF)
			root = make_astnode(AST_AND, parser);
		else if (parser->tokens[parser->indx]->type == TOKEN_OR_IF)
			root = make_astnode(AST_OR, parser);
		if (parser->status == ERR_ALLOC)
			return (NULL);
		root->left = left_node;
		root->right = parse_pipeline(parser);
		node_compound_cmd(root, parser);
	}
	return (root);
}
