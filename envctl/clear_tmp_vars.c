/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tmp_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 04:41:11 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/16 04:41:11 by crirodr2         ###   ########.fr       */
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

void	clear_tmp_vars(t_hashtable env)
{
	ft_lstclear(&env[TMP_VAR], del_envvar);
}
