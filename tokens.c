/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:58:04 by karlarod          #+#    #+#             */
/*   Updated: 2025/08/19 19:34:14 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "Libft/libft.h"
#include <stdio.h>

void	lexer_destroy_tokens(t_token **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i] != NULL)
			free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
	tokens = NULL;
}

void	lexer_handle_error(t_arg_lexer *lexer)
{
	if (lexer->tokens != NULL)
		lexer_destroy_tokens(lexer->tokens);
}

void	token_realloc(t_arg_lexer *lexer)
{
	t_token	**reallocated_tokens;
	size_t		i;

	lexer->size = 2 * lexer->size;
	i = 0;
	reallocated_tokens = malloc(lexer->size * sizeof(t_token));
	if (reallocated_tokens == NULL)
	{
		lexer->status = LEX_ERR_ALLOC;
		lexer_handle_error(lexer);
		return;
	}
	while (i < lexer->count)
	{
		reallocated_tokens[i] = lexer->tokens[i];
		++i;
	}
}

void	lexer_make_token(t_arg_lexer *lexer, t_token_type cur_token)
{
	size_t	len;

	len = 0;
	if (lexer->count == lexer->size - 1)
	{
		token_realloc(lexer);
		if (lexer->status == LEX_ERR_ALLOC)
			return;
	}
	lexer->tokens[lexer->count] = malloc(sizeof(t_token));
	if (lexer->tokens[lexer->count] == NULL)
	{
		lexer->status = LEX_ERR_ALLOC;
		lexer_handle_error(lexer);
		return;
	}
	len = (lexer->line + lexer->pos) - lexer->start_word ;
	lexer->tokens[lexer->count]->value = ft_substr(lexer->start_word, 0, len);
	lexer->tokens[lexer->count]->type = cur_token;
	lexer->start_word = NULL;
	if(lexer->line[lexer->pos] == '\0')
		lexer->previous_token = TOKEN_EOF;
	else
		lexer->previous_token = cur_token;
	++lexer->count;
	lexer->tokens[lexer->count] = NULL;
}

void lexer_init(t_arg_lexer	*lexer, char *line)
{
	lexer->line = line;
	lexer->size = 32;
	lexer->tokens = malloc(32 * sizeof(t_token));
	if (lexer->tokens == NULL)
		lexer->status = LEX_ERR_ALLOC;
}

void	print_tokens(t_token	**tokens)
{
	int		i;

	i = 0;
	static const char *token_type_str[] = {
		"WORD",
		"PIPE",
		"AND_IF",
		"OR_IF",
		"ASSIGNMENT",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HERE_DOC",
		"DELIMITER",
		"L_PARENTHESES",
		"R_PARENTHESES",
		"UNKOWN",
		"DOLLAR",
		"TOK_EOF"
	};
	while ( tokens[i] != NULL)
	{
		printf("type = %s\t value = %s\n", token_type_str[tokens[i]->type], tokens[i]->value);
		++i;
	}
}

t_token	**tokenize_line(char	*line)
{
	t_arg_lexer	lexer;

	lexer = (t_arg_lexer){};
	lexer_init(&lexer, line);
	if(lexer.status != LEX_OK)
		return(lexer_handle_error(&lexer), NULL);
	while (lexer.status == LEX_OK && lexer.previous_token != TOKEN_EOF)
	{
		if (ft_strchr(IFS, line[lexer.pos]) != NULL || line[lexer.pos] == '#' || line[lexer.pos] == '\0')
			lexer_default_state(&lexer);
		else if (ft_strchr (OPERATORS, line[lexer.pos]) != NULL)
			lexer_operator_state(&lexer);
		else if (line[lexer.pos] == '\'')
			lexer_squote_state(&lexer);
		else if (line[lexer.pos] == '"')
			lexer_dquote_state(&lexer);
		else
			lexer_word_state(&lexer);
	}
	if (lexer.status != LEX_OK)
		lexer_handle_error(&lexer);
	return(lexer.tokens);
}
