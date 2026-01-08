/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:27:05 by crirodr2          #+#    #+#             */
/*   Updated: 2025/10/16 20:23:40 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
#include "libft.h"

t_envvar	*lookup_env_lst(char *name, t_list	*env_lst)
{
	while (env_lst)
	{
		if (!ft_strncmp(((t_envvar *)(env_lst->content))->name,
			name, -1))
			return ((t_envvar *)(env_lst->content));
		env_lst = env_lst->next;
	}
	return (NULL);
}

t_envvar	*lookup_tmp_var(char *name, t_hashtable env)
{
	t_envvar	*envar;

	envar = lookup_env_lst(name, env[TMP_VAR]);
	return (envar);
}

t_envvar	*lookup_env_var(char *name, t_hashtable env)
{
	t_envvar	*envar;

	if (!ft_strncmp(name, "?", -1))
		return (lookup_env_lst("?", env[EXITSTAT_VAR]));
	envar = lookup_env_lst(name, env[TMP_VAR]);
	if (envar)
		return (envar);
	envar = lookup_env_lst(name, env[hash(name)]);
	return (envar);
}

char	*lookup_env_var_value(char *name, t_hashtable env)
{
	t_envvar	*envvar;

	envvar = lookup_env_var(name, env);
	if (!envvar)
		return (NULL);
	return (envvar->value);
}
