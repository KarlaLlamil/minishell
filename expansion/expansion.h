/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 04:15:08 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 06:36:20 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "ast.h"

typedef enum e_quote_t
{
	SINGEL,
	DOUBLE
}	t_quote_t;

typedef struct s_expansion
{
	char		*name;
	char		*end_name;
	char		*next;
	char		*value;
	char		*line;
	char		*start_quotes;
	char		*end_quotes;
	bool		in_quotes;
	t_quote_t	type;	
	bool		expand;
	int			status;
}	t_expansion;

int		expand_cmd(t_command *cmd, t_hashtable env);
void	del_args(char **args);
void	remove_quotes(char *str, t_expansion *expander);
int		expand_assignment(t_list *assignments, t_hashtable env );
void	is_expandable( t_expansion *expander);
void	is_quoted(char *arg, t_expansion *expander);
int		not_expandable_var(char *expanded, t_expansion *expander);
int		value_not_null( char *expanded, t_expansion *expander);
int		value_null( char *expanded, t_expansion *expander);
int		substitute_var_cmds(char *arg, t_expansion *expander, t_hashtable env);
int		substitute_args(t_command *cmd, int i, t_expansion *expander);
int		count_new_args(char *new);

#endif
