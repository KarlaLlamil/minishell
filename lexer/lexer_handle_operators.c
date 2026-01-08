/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_operators.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:35:46 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 06:49:57 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

static bool	handle_fd(t_arg_lexer *lexer)
{
	int		i;

	i = 0;
	if (lexer->start_word == NULL)
		return (false);
	while (ft_strchr(OPERATORS, lexer->start_word[i]) == NULL)
	{
		if (ft_isdigit(lexer->start_word[i]) == 0)
			return (false);
		i++;
	}
	if (i == 0 || (lexer->start_word[i] != '<' && lexer->start_word[i] != '>'))
		return (false);
	return (true);
}

static void	operators_one_char(t_arg_lexer *lexer)
{
	++lexer->pos;
	if (*lexer->start_word == '|')
		lexer_make_token(lexer, TOKEN_PIPE);
	else if (lexer->line[lexer->pos - 1] == '<')
		lexer_make_token(lexer, TOKEN_REDIR_IN);
	else if (lexer->line[lexer->pos - 1] == '>')
		lexer_make_token(lexer, TOKEN_REDIR_OUT);
	else if (*lexer->start_word == '(')
	{
		lexer->parenthesis = true;
		++lexer->n_parenthesis;
		lexer_make_token(lexer, TOKEN_L_PAREN);
	}
	else if (*lexer->start_word == ')')
	{
		--lexer->n_parenthesis;
		lexer->parenthesis = false;
		lexer_make_token(lexer, TOKEN_R_PAREN);
	}
}

static void	operators_two_chars(t_arg_lexer *lexer)
{
	lexer->pos = lexer->pos + 2;
	if (*lexer->start_word == '|')
		lexer_make_token(lexer, TOKEN_OR_IF);
	else if (lexer->line[lexer->pos - 2] == '<')
		lexer_make_token(lexer, TOKEN_HERE_DOC);
	else if (lexer->line[lexer->pos - 2] == '>')
		lexer_make_token(lexer, TOKEN_APPEND);
	else if (*lexer->start_word == '&')
		lexer_make_token(lexer, TOKEN_AND_IF);
}

void	lexer_operator_state(t_arg_lexer *lexer)
{
	bool	fd;

	fd = handle_fd(lexer);
	lexer->state = LEX_IN_OPERATOR;
	if (lexer->start_word != NULL && fd == false)
		lexer_make_token(lexer, TOKEN_WORD);
	if (lexer->status == LEX_ERR_ALLOC)
		return ;
	if (fd == false)
		lexer->start_word = &lexer->line[lexer->pos];
	if (lexer->line[lexer->pos] != lexer->line[lexer->pos + 1]
		|| lexer->line[lexer->pos] == '(' || lexer->line[lexer->pos] == ')')
		operators_one_char(lexer);
	else
		operators_two_chars(lexer);
}
