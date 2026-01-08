/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:57 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/18 13:44:58 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_PARSER_H
# define UTILITIES_PARSER_H

# include "ast.h"

void		del_asgmnt(void *ptr);
void		del_reddir(void *ptr);
void		del_args(char **args);
void		destroy_node(t_ast_node *node);
int			count_args(t_token **tokens, int indx);
bool		search_heredoc(t_ast_node *root, bool status, t_hashtable env);
t_ast_node	*cmd_just_assignments(t_parser *parser);
bool		is_redir(t_token_type type);
void		add_redir(t_list **redirs, t_parser *parser);
t_ast_node	*parse_simple_cmd(t_parser *parser);

#endif