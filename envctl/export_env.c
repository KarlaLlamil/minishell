/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:00:42 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 10:15:52 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "libft.h"
#include "./utils/utils.h"
#include <stdio.h>

static size_t	tmp_var_lst_size(t_hashtable env)
{
	size_t	size;
	t_list	*node;

	size = 0;
	node = env[TMP_VAR];
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}

static size_t	get_export_len(t_hashtable env)
{
	size_t	size;
	size_t	i;
	t_list	*node;

	size = tmp_var_lst_size(env);
	i = 0;
	while (i < HASHSIZE)
	{
		node = env[i];
		while (node)
		{
			if (((t_envvar *)(node->content))->export_env
				&& ((t_envvar *)(node->content))->value
				&& !lookup_tmp_var(((t_envvar *)(node->content))->name, env))
				size++;
			node = node->next;
		}
		i++;
	}
	return (size);
}

static void	helper_export_all(char	**export, t_list *node, size_t *explen)
{
	while (node)
	{
		export[*explen] = sepjoin(
				((t_envvar *)(node->content))->name,
				((t_envvar *)(node->content))->value,
				'=');
		if (export[*explen])
			(*explen)--;
		node = node->next;
	}
}

static void	helper_export_select(char	**export, t_list *node, size_t *explen,
	t_hashtable env)
{
	while (node)
	{
		if (((t_envvar *)(node->content))->export_env
			&& ((t_envvar *)(node->content))->value
			&& !lookup_tmp_var(((t_envvar *)(node->content))->name, env))
		{
			export[*explen] = sepjoin(
					((t_envvar *)(node->content))->name,
					((t_envvar *)(node->content))->value,
					'=');
		}
		if (export[*explen])
			(*explen)--;
		node = node->next;
	}
}

char	**export_env(t_hashtable env)
{
	size_t	i;
	char	**export;
	size_t	explen;

	explen = get_export_len(env);
	export = (char **)ft_calloc(explen + 1, sizeof(char *));
	if (!export)
		return (NULL);
	export[explen--] = NULL;
	helper_export_all(export, env[TMP_VAR], &explen);
	i = 0;
	while (i < HASHSIZE)
		helper_export_select(export, env[i++], &explen, env);
	if (explen != (size_t) -1)
		free_arr(&export);
	return (export);
}
