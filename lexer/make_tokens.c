/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:37:27 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/18 13:37:28 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

void	token_realloc(t_arg_lexer *lexer)
{
	t_token	**reallocated_tokens;
	size_t	i;

	lexer->size = 2 * lexer->size;
	i = 0;
	reallocated_tokens = malloc(lexer->size * sizeof(t_token));
	if (reallocated_tokens == NULL)
	{
		lexer->status = LEX_ERR_ALLOC;
		return ;
	}
	while (i < lexer->count)
	{
		reallocated_tokens[i] = lexer->tokens[i];
		++i;
	}
}

void	alloc_token(t_arg_lexer *lexer, t_token_type cur_token)
{
	if (lexer->count == lexer->size - 1)
	{
		token_realloc(lexer);
		if (lexer->status == LEX_ERR_ALLOC)
			return ;
	}
	lexer->tokens[lexer->count] = malloc(sizeof(t_token));
	if (lexer->tokens[lexer->count] == NULL)
	{
		lexer->status = LEX_ERR_ALLOC;
		return ;
	}
	lexer->tokens[lexer->count]->type = cur_token;
	lexer->tokens[lexer->count]->fd = -1;
}

void	lexer_make_token(t_arg_lexer *lexer, t_token_type cur_token)
{
	size_t	len;

	alloc_token(lexer, cur_token);
	if (lexer->status == LEX_ERR_ALLOC)
		return ;
	if (cur_token != TOKEN_WORD && ft_isdigit(lexer->start_word[0]) != 0)
	{
		lexer->tokens[lexer->count]->fd = ft_atoi(lexer->start_word);
		while (ft_isdigit(lexer->start_word[0]) != 0)
			++lexer->start_word;
	}
	len = (lexer->line + lexer->pos) - lexer->start_word;
	lexer->tokens[lexer->count]->value = ft_substr(lexer->start_word, 0, len);
	if (lexer->tokens[lexer->count]->value == NULL)
	{
		lexer->status = LEX_ERR_ALLOC;
		return ;
	}
	lexer->start_word = NULL;
	if (lexer->line[lexer->pos] == '\0')
		lexer->previous_token = TOKEN_EOF;
	else
		lexer->previous_token = cur_token;
	++lexer->count;
	lexer->tokens[lexer->count] = NULL;
}
