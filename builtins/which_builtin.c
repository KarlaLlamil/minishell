/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:13:17 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 14:15:40 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stddef.h>

t_builtin_type	which_builtin(char *cmd)
{
	int			i;
	const char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(builtins[i], cmd, -1))
			return (i);
		i++;
	}
	return (NOT_BUILTIN);
}
