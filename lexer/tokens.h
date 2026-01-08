/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:37:59 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 13:48:06 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stdbool.h>
# include <stddef.h>
# define IFS " \t\n"
# define OPERATORS "<>|&()"

# include "hash.h"

typedef enum e_lex_exit_status
{
	LEX_OK,
	LEX_ERR_ALLOC,
	LEX_ERR_UNCLOSED_QUOTE,
	LEX_ERR_UNCLOSED_PAREN
}	t_lex_exit_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HERE_DOC,
	TOKEN_L_PAREN,
	TOKEN_R_PAREN,
	TOKEN_EOF
}	t_token_type;

typedef enum e_lexer_state
{
	LEX_DEFAULT,
	LEX_IN_SQUOTES,
	LEX_IN_DQUOTES,
	LEX_IN_OPERATOR,
	LEX_IN_WORD
}	t_lexer_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				fd;

}	t_token;

typedef struct s_arg_lexer
{
	t_lexer_state		state;
	t_token				**tokens;
	char				*start_word;
	t_token_type		previous_token;
	char				*line;
	size_t				pos;
	size_t				size;
	size_t				count;
	t_lex_exit_status	status;
	bool				parenthesis;
	int					n_parenthesis;

}	t_arg_lexer;

int		tokenize_line(char	*line, t_hashtable env);
void	lexer_make_token(t_arg_lexer *lexer, t_token_type cur_token);
void	lexer_destroy_tokens(t_token **tokens);

#endif