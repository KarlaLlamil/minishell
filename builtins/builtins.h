/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:15:28 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 16:33:40 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "hash.h"

typedef enum e_builtin_type
{
	NOT_BUILTIN = -1,
	ECHO_CMD = 0,
	CD_CMD,
	PWD_CMD,
	EXPORT_CMD,
	UNSET_CMD,
	ENV_CMD,
	EXIT_CMD
}	t_builtin_type;

typedef int	(*t_builtin_cmd)(char **cmd_args, t_hashtable env);

t_builtin_type	which_builtin(char *cmd);
int				exec_builtin(char **cmd_args, t_hashtable env);
int				pwd_cmd(char **cmd_args, t_hashtable env);
int				cd_cmd(char **cmd_args, t_hashtable env);
int				echo_cmd(char **cmd_args, t_hashtable env);
int				env_cmd(char **cmd_args, t_hashtable env);
int				unset_cmd(char **cmd_args, t_hashtable env);
int				export_cmd(char **cmd_args, t_hashtable env);
char			**meta_export(t_hashtable env);
int				exit_cmd(char **cmd_args, t_hashtable env);
void			do_nothing_builtins(char **cmd_args, t_hashtable env);

#endif
