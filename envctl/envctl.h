/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envctl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:23:13 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 16:19:53 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVCTL_H
# define ENVCTL_H

# include "hash.h"
# include "ast.h"
# include "libft.h"
# include <stdbool.h>

unsigned int	hash(char *s);
int				init_env(t_hashtable env, char **env_import);
int				init_env_with_environ(t_hashtable env);
int				set_env_var(char *name, char *value, bool export_env,
					t_hashtable env);
t_envvar		*lookup_env_var(char *name, t_hashtable env);
char			*lookup_env_var_value(char *name, t_hashtable env);
t_envvar		*lookup_env_lst(char *name, t_list	*env_lst);
void			unset_env_var(char *name, t_hashtable env);
int				set_tmp_var(char *name, char *value, t_hashtable env);
t_envvar		*lookup_tmp_var(char *name, t_hashtable env);
int				lock_tmp_vars(t_hashtable env);
void			clear_tmp_vars(t_hashtable env);
char			**export_env(t_hashtable env);
int				set_exit_status_var(int value, t_hashtable env);
void			store_ast(t_ast_node *root, t_hashtable env);
void			clear_env(t_hashtable env);

#endif
