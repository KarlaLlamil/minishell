/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_delete_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:41:37 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/18 13:41:38 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdlib.h>

void	del_reddir(void *ptr)
{
	t_redir	*redir;

	redir = (t_redir *)ptr;
	free(redir->file);
	free(redir);
}

void	del_asgmnt(void *ptr)
{
	t_assignment	*assignment;

	assignment = (t_assignment *)ptr;
	free(assignment->name);
	free(assignment->value);
	free(assignment);
}

void	del_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		++i;
	}
	free(args);
}

void	destroy_node(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->left != NULL)
		destroy_node(node->left);
	if (node->right != NULL)
		destroy_node(node->right);
	if (node->type == AST_SIMPLE_CMD)
	{
		if (((t_command *)node->data)->assignments != NULL)
			ft_lstclear(&(((t_command *)node->data)->assignments), del_asgmnt);
		if (((t_command *)node->data)->arguments != NULL)
			del_args(((t_command *)node->data)->arguments);
		if (((t_command *)node->data)->redirs != NULL)
			ft_lstclear(&(((t_command *)node->data)->redirs), del_reddir);
		free(node->data);
	}
	if (node->type == AST_ASSIGNMENT)
	{
		if (((t_list *)node->data) != NULL)
			ft_lstclear((t_list **)&node->data, del_asgmnt);
	}
	free(node);
}
