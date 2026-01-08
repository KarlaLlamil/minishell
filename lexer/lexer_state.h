/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:38:28 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/18 13:38:29 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_STATE_H
# define LEXER_STATE_H

typedef struct s_arg_lexer	t_arg_lexer;

void	lexer_default_state(t_arg_lexer *lexer);
void	lexer_squote_state(t_arg_lexer *lexer);
void	lexer_dquote_state(t_arg_lexer *lexer);
void	lexer_operator_state(t_arg_lexer *lexer);
void	lexer_word_state(t_arg_lexer *lexer);
void	lexer_handle_error(t_arg_lexer *lexer);

#endif