/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:42:07 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 12:15:24 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ast.h"
#include "envctl.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>

static void	close_pipe(int pipefd[2])
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

static int	redir_and_cascade(bool rigth, int pipefd[2], t_ast_node *node,
	t_hashtable env)
{
	int			exit_status;
	int			oldfd;
	int			newfd;
	t_ast_node	*next_node;

	if (rigth)
	{
		oldfd = pipefd[0];
		newfd = STDIN_FILENO;
		next_node = node->right;
	}
	else
	{
		oldfd = pipefd[1];
		newfd = STDOUT_FILENO;
		next_node = node->left;
	}
	if (dup2(oldfd, newfd) == -1)
		return (perror("minishell: pipe error: dup2"), close_pipe(pipefd), -1);
	close_pipe(pipefd);
	exit_status = tree_interpreter(next_node, env);
	return (exit_status);
}

static pid_t	set_half_pipe(bool rigth, int pipefd[2], t_ast_node *node,
	t_hashtable env)
{
	pid_t	pipe_pid;
	pid_t	exit_status;

	pipe_pid = fork();
	if (pipe_pid == -1)
		return (perror("minishell: forking error:"), close_pipe(pipefd), -1);
	if (pipe_pid == 0)
	{
		exit_status = redir_and_cascade(rigth, pipefd, node, env);
		clear_env(env);
		rl_clear_history();
		exit(exit_status);
	}
	return (pipe_pid);
}

static int	pipe_exit_status(pid_t pipe_pid, t_hashtable env)
{
	int	wstatus;
	int	exit_status;

	waitpid(pipe_pid, &wstatus, 0);
	exit_status = 1;
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		exit_status = WTERMSIG(wstatus) + 128;
	if (set_exit_status_var(exit_status, env))
		perror("minishell: cannot store exit status in enviroment");
	return (exit_status);
}

int	do_pipe(t_ast_node *node, t_hashtable env)
{
	int		pipefd[2];
	pid_t	pipe_pid;
	int		exit_status;

	if (pipe(pipefd) == -1)
		return (perror("minishell: pipe error:"), -1);
	pipe_pid = set_half_pipe(false, pipefd, node, env);
	if (pipe_pid == -1)
		return (1);
	pipe_pid = set_half_pipe(true, pipefd, node, env);
	if (pipe_pid == -1)
		return (1);
	close_pipe(pipefd);
	exit_status = 0;
	if (!(node->root) || node->root->type != AST_PIPE)
		exit_status = pipe_exit_status(pipe_pid, env);
	while (wait(NULL) != -1)
		continue ;
	return (exit_status);
}
