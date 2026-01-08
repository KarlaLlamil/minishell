/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:58:04 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 16:51:24 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"
#include "lexer_state.h"
#include <errno.h>
#include "ast.h"
#include <stdio.h> 
#include <stdlib.h>

void	lexer_destroy_tokens(t_token **tokens)
{
	size_t	i;

	i = 0;
	if (tokens == NULL)
		return ;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->value != NULL)
			free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	lexer_handle_error(t_arg_lexer *lexer)
{
	if (lexer->tokens != NULL)
		lexer_destroy_tokens(lexer->tokens);
	if (lexer->status == LEX_ERR_ALLOC)
		perror ("Error allocating memory");
	else if (lexer->status == LEX_ERR_UNCLOSED_QUOTE)
		ft_putendl_fd("minishell: syntax error unclosed quotes", 2);
	else if (lexer->status == LEX_ERR_UNCLOSED_PAREN)
		ft_putendl_fd("minishell: syntax error unclosed parenthesis", 2);
}

static void	lexer_init(t_arg_lexer	*lexer, char *line)
{
	lexer->line = line;
	lexer->size = 32;
	lexer->n_parenthesis = 0;
	lexer->tokens = malloc(32 * sizeof(t_token));
	if (lexer->tokens == NULL)
		lexer->status = LEX_ERR_ALLOC;
	else
	{
		lexer->status = LEX_OK;
		lexer->tokens[0] = NULL;
	}
}

static void	ft_lexer(t_arg_lexer *lexer)
{
	while (lexer->status == LEX_OK && lexer->previous_token != TOKEN_EOF)
	{
		if (lexer->line[lexer->pos] == '#' || lexer->line[lexer->pos] == '\0'
			|| ft_strchr(IFS, lexer->line[lexer->pos]) != NULL)
			lexer_default_state(lexer);
		else if (ft_strchr (OPERATORS, lexer->line[lexer->pos]) != NULL)
			lexer_operator_state(lexer);
		else if (lexer->line[lexer->pos] == '\'')
			lexer_squote_state(lexer);
		else if (lexer->line[lexer->pos] == '"')
			lexer_dquote_state(lexer);
		else
			lexer_word_state(lexer);
	}
	if (lexer->status == LEX_OK
		&& (lexer->parenthesis == true || lexer->n_parenthesis != 0))
		lexer->status = LEX_ERR_UNCLOSED_PAREN;
}

int	tokenize_line(char *line, t_hashtable env)
{
	t_arg_lexer	lexer;

	if (*line == '\0')
		return (free(line), 1);
	lexer = (t_arg_lexer){};
	lexer_init(&lexer, line);
	if (lexer.status != LEX_OK)
	{
		lexer_handle_error(&lexer);
		free(line);
	}
	else
	{
		ft_lexer(&lexer);
		free(line);
		if (lexer.status != LEX_OK)
			lexer_handle_error(&lexer);
		else if (lexer.tokens[0] == NULL)
			lexer_destroy_tokens(lexer.tokens);
		else
			return (make_ast(lexer.tokens, env));
	}
	return (1);
}
