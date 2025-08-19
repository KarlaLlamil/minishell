/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_states.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:57:53 by karlarod          #+#    #+#             */
/*   Updated: 2025/08/17 19:57:54 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "Libft/libft.h"

void	lexer_default_state(t_arg_lexer *lexer)
{
	bool	comment;

	if (lexer->start_word != NULL)
		lexer_make_token(&lexer, lexer->start_word);
	comment = false;
	while (lexer->line[lexer->pos] != '\0')
	{
		if (lexer->line[lexer->pos] == '#')
			comment = true;
		if (comment == true || ft_strchr(IFS, lexer->line[lexer->pos] != NULL))
			++lexer->pos;
		else
			break;
	}
}

void	lexer_squote_state(t_arg_lexer *lexer)
{

}

void	lexer_dquote_state(t_arg_lexer *lexer)
{

}

void	lexer_operator_state(t_arg_lexer *lexer)
{

}

void	lexer_word_state(t_arg_lexer *lexer)
{
	
}