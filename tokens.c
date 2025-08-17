/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:58:04 by karlarod          #+#    #+#             */
/*   Updated: 2025/08/17 20:00:16 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokens.h>


void	lexer_destroy_tokens(t_token **tokens)
{
	
}

void	lexer_handle_error(t_arg_lexer *lexer)
{

}
void	lexer_make_token(t_arg_lexer *lexer)
{

}

void lexer_init(t_arg_lexer	*lexer, char *line)
{
	lexer->line = line;
	lexer->size = 32;
	lexer->tokens = malloc(32*sizeof(t_token));
	if (lexer->tokens != NULL)
		lexer->status = LEX_ERR_ALLOC;
}

t_token	**tokenize_line(char	*line)
{
	t_arg_lexer	lexer;

	lexer = (t_arg_lexer){};
	lexer_init(&lexer, line);
	if(lexer.exit_status != LEX_OK)
		return(lexer_handle_error(&lexer), NULL);
	while (lexer.status == LEX_OK && lexer.previous_token != TOKEN_EOF)
	{
		
	}

}
