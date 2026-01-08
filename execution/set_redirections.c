/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 00:03:42 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 12:16:30 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int	undo_redirections(int stdio_bckup[2])
{
	int	err;

	err = 0;
	if (dup2(stdio_bckup[0], STDIN_FILENO) == -1)
		err = 1;
	if (dup2(stdio_bckup[1], STDOUT_FILENO) == -1)
		err = 1;
	close(stdio_bckup[0]);
	close(stdio_bckup[1]);
	if (err)
		perror("minishell: redirection error");
	return (0);
}

static int	open_redir_file(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == TOKEN_REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, (O_CREAT | O_WRONLY | O_TRUNC),
				(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	else if (redir->type == TOKEN_APPEND)
		fd = open(redir->file, (O_CREAT | O_WRONLY | O_APPEND),
				(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	else if (redir->type == TOKEN_HERE_DOC)
		fd = redir->fd_here_doc;
	return (fd);
}

static int	backup_stdio(int stdio_bckup[2])
{
	if (stdio_bckup)
	{
		stdio_bckup[0] = dup(STDIN_FILENO);
		stdio_bckup[1] = dup(STDOUT_FILENO);
	}
	if (stdio_bckup && (stdio_bckup[0] == -1 || stdio_bckup[1] == -1))
	{
		if (stdio_bckup[0] != -1)
			close(stdio_bckup[0]);
		if (stdio_bckup[1] != -1)
			close(stdio_bckup[1]);
		return (1);
	}
	return (0);
}

int	set_redirections(t_list *redirs_lst, int stdio_bckup[2])
{
	t_redir	*redir;
	int		tmp_fd;
	int		err;

	if (backup_stdio(stdio_bckup))
		return (perror("minishell: redirection error"), 1);
	while (redirs_lst)
	{
		redir = (t_redir *)(redirs_lst->content);
		tmp_fd = open_redir_file(redir);
		if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HERE_DOC)
			err = (tmp_fd < 0 || dup2(tmp_fd, STDIN_FILENO) == -1);
		else
			err = (tmp_fd < 0 || dup2(tmp_fd, STDOUT_FILENO) == -1);
		if (err)
		{
			perror("minishell: redirection error");
			undo_redirections(stdio_bckup);
			return (1);
		}
		close(tmp_fd);
		redirs_lst = redirs_lst->next;
	}
	return (0);
}
