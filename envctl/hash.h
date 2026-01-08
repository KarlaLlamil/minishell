/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:44:33 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/19 21:09:41 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# define HASHSIZE 101
# define TMP_VAR 101	// (HASHSIZE)
# define EXITSTAT_VAR 102	// (HASHSIZE + 1)
# define AST_VAR 103	// (HASHSIZE + 2)

# include "libft.h"
# include <stdbool.h>

typedef t_list	*t_hashtable[101 + 3];	// (HASHSIZE + 3)

typedef struct s_enviroment_variable
{
	char	*name;
	char	*value;
	bool	export_env;
}	t_envvar;

#endif
