/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:37:04 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 13:47:23 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "ast.h"
#include "expansion.h"
#include "envctl.h"
#include "./utils/utils.h"
#include "signaling.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <sys/stat.h>

static char	*check_exe_path(char *file_name, int *exit_status, t_hashtable env)
{
	char		*path;
	struct stat	file;

	*exit_status = 0;
	path = find_path(file_name, env);
	if (!path || access(path, F_OK))
	{
		*exit_status = 127;
		ft_putstr_fd(file_name, 2);
		if (!path)
			ft_putendl_fd(": command not found", 2);
		else
			ft_putendl_fd(": No such file or directory", 2);
	}
	stat(path, &file);
	if (!(*exit_status) && (access(path, X_OK) || S_ISDIR(file.st_mode)))
	{
		*exit_status = 126;
		ft_putstr_fd(file_name, 2);
		if (S_ISDIR(file.st_mode))
			ft_putendl_fd(": Is a directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
	}
	return (path);
}

static void	exec_wrap(t_command *cmd_info, t_hashtable env)
{
	char	*cmd_path;
	char	**env_arr;
	int		exit_status;

	cmd_path = check_exe_path((cmd_info->arguments)[0], &exit_status, env);
	env_arr = export_env(env);
	if (!env_arr)
	{
		perror("minishell: export_env: no enviroment export array generated");
		exit_status = exit_status || 1;
	}
	if (!exit_status)
	{
		set_default_signals();
		execve(cmd_path, cmd_info->arguments, env_arr);
		ft_putstr_fd((cmd_info->arguments)[0], STDERR_FILENO);
		perror(": error executing the command");
		exit_status = 1;
	}
	free_arr(&env_arr);
	free(cmd_path);
	clear_env(env);
	rl_clear_history();
	exit(exit_status);
}

static	int	exec_non_builtin(t_command *cmd_info, t_hashtable env)
{
	pid_t	cpid;
	int		exit_status;
	int		wstatus;

	cpid = fork();
	if (cpid == -1)
		return (perror("minishell: forking error:"), -1);
	if (cpid == 0)
		exec_wrap(cmd_info, env);
	waitpid(cpid, &wstatus, 0);
	exit_status = 1;
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		exit_status = WTERMSIG(wstatus) + 128;
	return (exit_status);
}

static int	expansion_and_setup(t_command *cmd_info, t_hashtable env,
	int stdio_bckup[2])
{
	int	err;

	err = 0;
	if (expand_cmd(cmd_info, env))
	{
		perror("minishell: cannot process command");
		err = 1;
	}
	if (err || set_redirections(cmd_info->redirs, stdio_bckup))
	{
		if (set_exit_status_var(1, env))
			perror("minishell: cannot store exit status in enviroment");
		return (1);
	}
	return (0);
}

int	execute_command(t_ast_node *cmd_node, t_hashtable env)
{
	t_command	*cmd_info;
	int			exit_status;
	int			stdio_bckup[2];

	cmd_info = (t_command *)(cmd_node->data);
	if (expansion_and_setup(cmd_info, env, stdio_bckup))
		return (1);
	if (cmd_info->arguments == NULL || cmd_info->arguments[0] == NULL)
		exit_status = 0;
	else if (which_builtin((cmd_info->arguments)[0]) != NOT_BUILTIN)
		exit_status = exec_builtin(cmd_info->arguments, env);
	else
		exit_status = exec_non_builtin(cmd_info, env);
	undo_redirections(stdio_bckup);
	clear_tmp_vars(env);
	if (set_exit_status_var(exit_status, env))
		perror("minishell: cannot store exit status in enviroment");
	return (exit_status);
}
