/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:20:40 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/19 20:50:20 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "libft.h"
#include <stdlib.h>

static t_list	**lookup_tmp_envvar_ptr(char *name, t_hashtable env)
{
	t_list	**key_list;

	key_list = &env[TMP_VAR];
	while (*key_list)
	{
		if (!ft_strncmp(((t_envvar *)((*key_list)->content))->name,
			name, -1))
			return (key_list);
		key_list = &((*key_list)->next);
	}
	return (NULL);
}

static t_list	**lookup_envvar_ptr(char *name, t_hashtable env)
{
	t_list	**key_list;

	key_list = lookup_tmp_envvar_ptr(name, env);
	if (key_list)
		return (key_list);
	key_list = &env[hash(name)];
	while (*key_list)
	{
		if (!ft_strncmp(((t_envvar *)((*key_list)->content))->name,
			name, -1))
			return (key_list);
		key_list = &((*key_list)->next);
	}
	return (NULL);
}

void	unset_env_var(char *name, t_hashtable env)
{
	t_list	**pos;
	t_list	*node;

	pos = lookup_envvar_ptr(name, env);
	if (!pos)
		return ;
	node = *pos;
	*pos = node->next;
	free(((t_envvar *)(node->content))->name);
	free(((t_envvar *)(node->content))->value);
	free(((t_envvar *)(node->content)));
	free(node);
}
