/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:25:52 by crirodr2          #+#    #+#             */
/*   Updated: 2025/10/02 16:26:43 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envctl.h"

unsigned int	hash(char *s)
{
	unsigned int	hashval;

	hashval = 0;
	while (*s != '\0')
	{
		hashval = *s + 31 * hashval;
		s++;
	}
	return (hashval % HASHSIZE);
}
