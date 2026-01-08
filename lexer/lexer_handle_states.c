/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_states.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:57:53 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/18 13:36:49 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer_state.h"
#include "libft.h"
#include <stdlib.h>

void	lexer_default_state(t_arg_lexer *lexer)
{
	bool	comment;

	lexer->state = LEX_DEFAULT;
	if (lexer->start_word != NULL)
		lexer_make_token(lexer, TOKEN_WORD);
	if (lexer->status == LEX_ERR_ALLOC)
		return ;
	comment = false;
	while (lexer->line[lexer->pos] != '\0')
	{
		if (lexer->line[lexer->pos] == '#')
			comment = true;
		if (comment == true || ft_strchr(IFS, lexer->line[lexer->pos]) != NULL)
			++lexer->pos;
		else
			return ;
	}
	lexer->previous_token = TOKEN_EOF;
}

void	lexer_squote_state(t_arg_lexer *lexer)
{
	if (lexer->start_word == NULL)
		lexer->start_word = &lexer->line[lexer->pos];
	while (lexer->line[lexer->pos] != '\0')
	{
		if (lexer->line[lexer->pos] == '\'' && lexer->state != LEX_IN_SQUOTES)
			lexer->state = LEX_IN_SQUOTES;
		else if (lexer->line[lexer->pos] == '\''
			&& lexer->state == LEX_IN_SQUOTES)
		{
			lexer->state = LEX_IN_WORD;
			++lexer->pos;
			return ;
		}
		++lexer->pos;
	}
	lexer->status = LEX_ERR_UNCLOSED_QUOTE;
}

void	lexer_dquote_state(t_arg_lexer *lexer)
{
	if (lexer->start_word == NULL)
		lexer->start_word = &lexer->line[lexer->pos];
	while (lexer->line[lexer->pos] != '\0')
	{
		if (lexer->line[lexer->pos] == '"' && lexer->state != LEX_IN_DQUOTES)
			lexer->state = LEX_IN_DQUOTES;
		else if (lexer->line[lexer->pos] == '"'
			&& lexer->state == LEX_IN_DQUOTES)
		{
			lexer->state = LEX_IN_WORD;
			++lexer->pos;
			return ;
		}
		++lexer->pos;
	}
	lexer->status = LEX_ERR_UNCLOSED_QUOTE;
}

void	lexer_word_state(t_arg_lexer *lexer)
{
	lexer->state = LEX_IN_WORD;
	if (lexer->start_word == NULL)
		lexer->start_word = &lexer->line[lexer->pos];
	while (lexer->line[lexer->pos] != '\0' && lexer->status == LEX_OK)
	{
		if (ft_strchr(IFS, lexer->line[lexer->pos]) != NULL
			|| ft_strchr(OPERATORS, lexer->line[lexer->pos]) != NULL)
			return ;
		else if (lexer->line[lexer->pos] == '\'')
			lexer_squote_state(lexer);
		else if (lexer->line[lexer->pos] == '"')
			lexer_dquote_state(lexer);
		else
			++lexer->pos;
	}
}
