/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 01:18:27 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 17:21:11 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>
#include "here_doc.h"
#include "signaling.h"

static void	interrupted_heredoc(char *line, t_heredoc *heredoc)
{
	if (g_sigstat == SIG_SIGINT)
	{
		heredoc->status = false;
		if (line)
			free(line);
	}
	else
	{
		ft_printf("minishell: warning: here-doc delimited by end-of-file \
wanted \'%s\')\n", heredoc->delimiter);
	}
}

static void	writing_in_heredoc(char **line, t_heredoc *heredoc, t_hashtable env)
{
	if (heredoc->expand_vars == true)
	{
		if (ft_strchr(*line, '$'))
		{
			if (substitute_var_here_doc(line, env) == 0)
				heredoc->status = true;
		}
	}
	if (write(heredoc->fd, *line, ft_strlen(*line)) < 0)
		heredoc->status = false;
	if (write(heredoc->fd, "\n", 1) < 0)
		heredoc->status = false;
}

void	reading_heredoc(t_heredoc *heredoc, t_hashtable env)
{
	char	*line;

	set_heredoc_signals();
	while (heredoc->status == true)
	{
		line = readline("> ");
		if (g_sigstat == SIG_SIGINT || !line)
		{
			interrupted_heredoc(line, heredoc);
			return ;
		}
		if (ft_strncmp(heredoc->delimiter, line, -1) != 0)
			writing_in_heredoc(&line, heredoc, env);
		else
		{
			free(line);
			break ;
		}
		free(line);
	}
}
