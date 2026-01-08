/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_tmp_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:08:12 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 06:59:04 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"
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

int	lock_tmp_vars(t_hashtable env)
{
	t_list	*tmp_lst;
	int		err;

	err = 0;
	tmp_lst = env[TMP_VAR];
	while (tmp_lst)
	{
		err = set_env_var(
				((t_envvar *)(tmp_lst->content))->name,
				((t_envvar *)(tmp_lst->content))->value,
				false, env)
			|| err;
		tmp_lst = tmp_lst->next;
	}
	ft_lstclear(&env[TMP_VAR], del_envvar);
	return (err);
}
