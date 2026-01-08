/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 07:16:38 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 07:42:17 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*sepjoin(char const *s1, char const *s2, char sep)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	size_t	tmp;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = ft_calloc(len1 + len2 + 1 + 1, sizeof(char));
	if (!new)
		return (NULL);
	tmp = 0;
	while (tmp < len1)
	{
		new[tmp] = s1[tmp];
		tmp++;
	}
	new[tmp] = sep;
	tmp = 0;
	while (tmp < len2)
	{
		new[len1 + tmp + 1] = s2[tmp];
		tmp++;
	}
	new[len1 + len2 + 1] = '\0';
	return (new);
}
