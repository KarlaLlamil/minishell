/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:52 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 02:04:37 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utilities_parser.h"
#include "tokens.h"
#include <stdlib.h>
#include "libft.h"

bool	is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HERE_DOC);
}

static void	set_file_reddir(t_redir *new_reddir, t_parser *parser)
{
	if (parser->tokens[parser->indx] != NULL
		&& parser->tokens[parser->indx]->type == TOKEN_WORD)
	{
		new_reddir->file = ft_strdup(parser->tokens[parser->indx]->value);
		if (new_reddir->file == NULL)
			parser->status = ERR_ALLOC;
		++parser->indx;
	}
	else
	{
		new_reddir->file = NULL;
		parser->status = MISSING_FILE;
	}
}

void	add_redir(t_list **redirs, t_parser *parser)
{
	t_redir	*new_reddir;
	t_list	*new_node;

	new_reddir = malloc(sizeof(t_redir));
	if (new_reddir == NULL)
	{
		parser->status = ERR_ALLOC;
		return ;
	}
	new_reddir->type = parser->tokens[parser->indx]->type;
	if (new_reddir->type == TOKEN_HERE_DOC)
		parser->here_doc = true;
	new_reddir->fd = parser->tokens[parser->indx]->fd;
	++parser->indx;
	set_file_reddir(new_reddir, parser);
	new_node = ft_lstnew(new_reddir);
	ft_lstadd_back(redirs, new_node);
}
