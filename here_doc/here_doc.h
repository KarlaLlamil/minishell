/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 01:57:55 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 01:57:56 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "hash.h"
# include <stdbool.h>

# define VALID_NAME "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct s_heredoc
{
	char	*delimiter;
	bool	expand_vars;
	int		fd;
	char	*file_name;
	bool	status;
}	t_heredoc;

int		substitute_var_here_doc(char	**line, t_hashtable env);
void	reading_heredoc(t_heredoc *heredoc, t_hashtable env);
bool	ft_mkstmp(t_heredoc *heredoc);

#endif