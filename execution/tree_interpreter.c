/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:41:26 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 09:37:09 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "expansion.h"
#include "envctl.h"
#include "execution.h"
#include "signaling.h"
#include <stdio.h>

static int	put_assignations_in_env(t_list *assig, t_hashtable env)
{
	int	err;

	err = 0;
	expand_assignment(assig, env);
	err = err || lock_tmp_vars(env);
	if (err)
		perror("minishell: one or more variables could not be assigned");
	if (set_exit_status_var(err, env))
		perror("minishell: cannot store exit status in enviroment");
	return (err);
}

static int	conditional_execution(t_ast_node *node, t_hashtable env)
{
	int	exit_status;

	exit_status = tree_interpreter(node->left, env);
	if (node->type == AST_AND && !exit_status)
		return (tree_interpreter(node->right, env));
	if (node->type == AST_OR && exit_status)
		return (tree_interpreter(node->right, env));
	return (exit_status);
}

int	tree_interpreter(t_ast_node *node, t_hashtable env)
{
	if (!node)
		return (0);
	if (g_sigstat == SIG_SIGINT)
		return (128 + SIG_SIGINT);
	if (node->type == AST_SIMPLE_CMD)
		return (execute_command(node, env));
	else if (node->type == AST_PIPE)
		return (do_pipe(node, env));
	else if (node->type == AST_AND || node->type == AST_OR)
		return (conditional_execution(node, env));
	else if (node->type == AST_PARENTHESES)
		return (tree_interpreter(node->left, env));
	else if (node->type == AST_ASSIGNMENT)
		return (put_assignations_in_env((t_list *)(node->data), env));
	return (1);
}
