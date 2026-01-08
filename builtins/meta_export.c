/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:00:42 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 16:44:04 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "libft.h"
#include "./utils/utils.h"
#include <stdio.h>

static size_t	get_export_len(t_hashtable env)
{
	size_t	size;
	size_t	i;
	t_list	*node;

	size = 0;
	i = 0;
	while (i < HASHSIZE)
	{
		node = env[i];
		while (node)
		{
			if (((t_envvar *)(node->content))->export_env)
				size++;
			node = node->next;
		}
		i++;
	}
	return (size);
}

static void	helper_export(char	**export, t_list *node, size_t *explen)
{
	while (node)
	{
		if (((t_envvar *)(node->content))->export_env)
		{
			if (((t_envvar *)(node->content))->value)
			{
				export[*explen] = sepjoin(
						((t_envvar *)(node->content))->name,
						((t_envvar *)(node->content))->value,
						'=');
			}
			else
			{
				export[*explen] = ft_strdup(
						((t_envvar *)(node->content))->name);
			}
		}
		if (export[*explen])
			(*explen)--;
		node = node->next;
	}
}

static size_t	size_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static void	sort_env_arr(char ***env_arr)
{
	size_t	i;
	size_t	j;
	size_t	n;
	char	*tmp;

	n = size_arr(*env_arr);
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strncmp((*env_arr)[j], (*env_arr)[j + 1], -1) > 0)
			{
				tmp = (*env_arr)[j];
				(*env_arr)[j] = (*env_arr)[j + 1];
				(*env_arr)[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**meta_export(t_hashtable env)
{
	size_t	i;
	char	**export;
	size_t	explen;

	explen = get_export_len(env);
	export = (char **)ft_calloc(explen + 1, sizeof(char *));
	if (!export)
		return (NULL);
	export[explen--] = NULL;
	i = 0;
	while (i < HASHSIZE)
		helper_export(export, env[i++], &explen);
	if (explen != (size_t) -1)
		return (free_arr(&export), NULL);
	sort_env_arr(&export);
	return (export);
}
