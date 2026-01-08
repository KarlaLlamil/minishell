/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:49:08 by crirodr2          #+#    #+#             */
/*   Updated: 2025/10/07 19:39:01 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "ast.h"
#include "libft.h"
#include <stdlib.h>

static void	del_envvar(void *envar)
{
	t_envvar	*var;

	var = (t_envvar *)envar;
	free(var->name);
	free(var->value);
	free(var);
}

static void	destroy_ast_mask(void *root)
{
	destroy_ast((t_ast_node *)root);
}

void	clear_env(t_hashtable env)
{
	size_t	i;

	i = 0;
	while (i < HASHSIZE)
	{
		ft_lstclear(&env[i], del_envvar);
		i++;
	}
	ft_lstclear(&env[TMP_VAR], del_envvar);
	ft_lstclear(&env[EXITSTAT_VAR], del_envvar);
	ft_lstclear(&env[AST_VAR], destroy_ast_mask);
	ft_bzero(env, sizeof(t_hashtable));
}
