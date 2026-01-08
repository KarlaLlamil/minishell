/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 01:55:13 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 15:59:45 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>
#include "ast.h"
#include "here_doc.h"
#include "expansion.h"
#include "signaling.h"

static bool	here_doc_delimiter(char *delimiter, t_heredoc *heredoc)
{
	t_expansion	quotes;

	quotes = (t_expansion){};
	heredoc->delimiter = ft_strdup(delimiter);
	if (heredoc->delimiter == NULL)
		return (false);
	heredoc->status = true;
	heredoc->expand_vars = true;
	is_quoted(heredoc->delimiter, &quotes);
	if (quotes.in_quotes == true)
	{
		heredoc->expand_vars = false;
		remove_quotes(heredoc->delimiter, &quotes);
	}
	return (true);
}

static bool	setup_heredoc(t_list *redir, t_hashtable env )
{
	t_heredoc	heredoc;

	heredoc = (t_heredoc){};
	if (!here_doc_delimiter(((t_redir *)redir->content)->file, &heredoc))
		return (false);
	if (ft_mkstmp(&heredoc) == false)
		return (free(heredoc.delimiter), false);
	reading_heredoc(&heredoc, env);
	free(heredoc.delimiter);
	close(heredoc.fd);
	if (heredoc.status == true)
	{
		heredoc.fd = open(heredoc.file_name, O_RDONLY);
		if (heredoc.fd < 0)
			heredoc.status = false;
	}
	unlink(heredoc.file_name);
	free(heredoc.file_name);
	if (heredoc.status == false)
		return (false);
	free(((t_redir *)redir->content)->file);
	((t_redir *)redir->content)->file = NULL;
	((t_redir *)redir->content)->fd_here_doc = heredoc.fd;
	return (true);
}

bool	search_heredoc(t_ast_node *root, bool status, t_hashtable env)
{
	t_list	*lst_redirs;

	if (root == NULL || g_sigstat == SIG_SIGINT)
		return (status);
	search_heredoc(root->left, status, env);
	search_heredoc(root->right, status, env);
	if (root->type == AST_SIMPLE_CMD)
	{
		lst_redirs = ((t_command *)root->data)->redirs;
		while (lst_redirs != NULL && status == true)
		{
			if (((t_redir *)lst_redirs->content)->type == TOKEN_HERE_DOC)
			{
				status = setup_heredoc(lst_redirs, env);
				if (status == false)
					return (status);
			}
			lst_redirs = lst_redirs->next;
		}
	}
	return (status);
}
