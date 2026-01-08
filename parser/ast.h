/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:44:07 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 14:54:43 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <stdbool.h>
# include "libft.h"
# include "tokens.h"
# include "hash.h"

typedef enum e_node_type
{
	AST_SIMPLE_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_PARENTHESES,
	AST_ASSIGNMENT
}	t_node_type;

typedef enum e_ast_exit_status
{
	OK,
	ERR_ALLOC,
	MISSING_PARENTHESES,
	MISSING_FILE,
	INCOMPLETE_PIPE,
	INCOMPLETE_AND,
	INCOMPLETE_OR
}	t_ast_exit_status;

typedef struct s_command
{
	t_list	*assignments;
	char	**arguments;
	int		n_args;
	t_list	*redirs;
}	t_command;

typedef struct s_redir
{
	t_token_type	type;
	int				fd;
	char			*file;
	int				fd_here_doc;
}	t_redir;

typedef struct s_assignment
{
	char	*name;
	char	*value;
	bool	export_env;
}	t_assignment;

typedef struct s_ast_node
{
	t_node_type			type;
	void				*data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*root;
}	t_ast_node;

typedef struct s_parser
{
	t_token				**tokens;
	t_ast_exit_status	status;
	bool				here_doc;
	int					indx;
}	t_parser;

int			make_ast(t_token **tokens, t_hashtable env);
t_ast_node	*parse_compoud_cmd( t_parser *parser);
t_ast_node	*make_astnode(t_node_type type, t_parser *parser);
bool		is_assigmnt(char	*str);
void		add_assignment(t_list **assignment, t_parser *parser, bool export);
void		print_tree(t_ast_node *root, int level);
void		destroy_ast(t_ast_node	*root);
bool		search_heredoc(t_ast_node *root, bool status, t_hashtable env);
bool		is_valid_name(char **str);

#endif
