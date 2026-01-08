/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 03:44:14 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 06:59:05 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "ast.h"
#include "libft.h"

static void	destroy_ast_mask(void *root)
{
	destroy_ast((t_ast_node *)root);
}

void	store_ast(t_ast_node *root, t_hashtable env)
{
	t_list	*var_lst;

	if (env[AST_VAR])
		ft_lstclear(&(env[AST_VAR]), destroy_ast_mask);
	var_lst = ft_lstnew(root);
	if (!var_lst)
		return ;
	ft_lstadd_front(&(env[AST_VAR]), var_lst);
}
