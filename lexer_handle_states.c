/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_states.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:57:53 by karlarod          #+#    #+#             */
/*   Updated: 2025/08/19 20:01:00 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "Libft/libft.h"

//revisar en WORD " ', si tengo que hacer algo en este punto para '=' y para '$'
//me falta agrgar '$' "?" '*' en los tokens???
void	lexer_default_state(t_arg_lexer *lexer)
{
	bool	comment;

	lexer->state = LEX_DEFAULT;
	if (lexer->start_word != NULL)
		lexer_make_token(lexer, TOKEN_WORD);
	comment = false;
	while (lexer->line[lexer->pos] != '\0')
	{
		if (lexer->line[lexer->pos] == '#')
			comment = true;
		if (comment == true || ft_strchr(IFS, lexer->line[lexer->pos]) != NULL)
			++lexer->pos;
		else
			return;
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
		else if (lexer->line[lexer->pos] == '\'' && lexer->state == LEX_IN_SQUOTES)
		{
			lexer->state = LEX_IN_WORD;
			return;
		}
		++lexer->pos;
	}
}

void	lexer_dquote_state(t_arg_lexer *lexer)
{
	if (lexer->start_word == NULL)
		lexer->start_word = &lexer->line[lexer->pos];
	while (lexer->line[lexer->pos] != '\0')
	{
		if (lexer->line[lexer->pos] == '"' && lexer->state != LEX_IN_DQUOTES)
			lexer->state = LEX_IN_DQUOTES;
		else if (lexer->line[lexer->pos] == '"' && lexer->state == LEX_IN_DQUOTES)
		{
			lexer->state = LEX_IN_WORD;
			return;
		}
		else if (lexer->line[lexer->pos] == '$')
		{
			lexer_operator_state(lexer);
			if (lexer->line[lexer->pos] == '\0')
				lexer->previous_token = TOKEN_EOF;
			else
				lexer->start_word = &lexer->line[lexer->pos];
		}
		++lexer->pos;
	}
}

void	lexer_operator_state(t_arg_lexer *lexer)
{
	lexer->state = LEX_IN_OPERATOR;
	if (lexer->start_word != NULL)
	{
		if (ft_strchr("<>", lexer->line[lexer->pos]) && )
		lexer_make_token(lexer, TOKEN_WORD);
	}
	if (lexer->line[lexer->pos ] != lexer->line[lexer->pos + 1])
	{
		lexer->start_word = &lexer->line[lexer->pos];
		++lexer->pos;
		if (*lexer->start_word == '|')
			lexer_make_token(lexer, TOKEN_PIPE);
		else if (*lexer->start_word == '<')
			lexer_make_token(lexer, TOKEN_REDIR_IN);
		else if (*lexer->start_word == '>')
			lexer_make_token(lexer, TOKEN_REDIR_OUT);
		else if (*lexer->start_word == '(')
			lexer_make_token(lexer, TOKEN_L_PAREN);
		else if (*lexer->start_word == ')')
			lexer_make_token(lexer, TOKEN_R_PAREN);
		else if (*lexer->start_word == '$')
			lexer_make_token(lexer, TOKEN_DOLLAR);
	}
	else
	{
		lexer->start_word = &lexer->line[lexer->pos];
		lexer->pos = lexer->pos + 2;
		if (*lexer->start_word == '|')
			lexer_make_token(lexer, TOKEN_OR_IF);
		else if (*lexer->start_word == '<')
			lexer_make_token(lexer, TOKEN_HERE_DOC); //FALTA TRATAR EL HEREDOC
		else if (*lexer->start_word == '>')
			lexer_make_token(lexer, TOKEN_APPEND);
		else if (*lexer->start_word == '&')
			lexer_make_token(lexer, TOKEN_AND_IF);
	}
}

void	lexer_word_state(t_arg_lexer *lexer)
{
	lexer->state = LEX_IN_WORD;
	if (lexer->start_word == NULL)
		lexer->start_word = &lexer->line[lexer->pos];
	while (lexer->line[lexer->pos] != '\0')
	{
		if (ft_strchr(IFS, lexer->line[lexer->pos]) != NULL || ft_strchr(OPERATORS, lexer->line[lexer->pos]) != NULL)
			return;
		if (lexer->line[lexer->pos] == '\'')
			lexer_squote_state(lexer);
		else if (lexer->line[lexer->pos] == '"')
			lexer_dquote_state(lexer);
		++lexer->pos;
	}
	
}