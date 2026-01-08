/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 03:11:43 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 09:22:01 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "hash.h"
# include "ast.h"

int		execute_command(t_ast_node *cmd_node, t_hashtable env);
int		tree_interpreter(t_ast_node *node, t_hashtable env);
int		do_pipe(t_ast_node *node, t_hashtable env);
char	*find_path(char *cmd_name, t_hashtable env);
int		set_redirections(t_list *redirs_lst, int stdio_bckup[2]);
int		undo_redirections(int stdio_bckup[2]);

#endif
