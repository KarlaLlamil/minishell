/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:09:57 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 15:08:51 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "envctl.h"
#include "signaling.h"
#include "execution.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*rl_gets(void)
{
	char	*line_read;

	line_read = readline("$ ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

static void	main_loop(t_hashtable env)
{
	char		*input;

	while (1)
	{
		set_prompt_signals();
		input = rl_gets();
		if (!input)
			break ;
		if (tokenize_line(input, env))
			continue ;
		if (!env[AST_VAR])
		{
			perror("minishell: internal error");
			continue ;
		}
		set_execution_signals();
		tree_interpreter((t_ast_node *)(env[AST_VAR]->content), env);
		while (wait(NULL) != -1)
			continue ;
		if (g_sigstat == SIG_SIGINT)
			write_to_tty("\n");
	}
}

int	main(void)
{
	t_hashtable	env;
	int			exit_status;
	char		*es_str;

	if (init_env_with_environ(env))
		return (ft_putendl_fd("Abort", STDERR_FILENO), 1);
	main_loop(env);
	es_str = lookup_env_var_value("?", env);
	exit_status = 1;
	if (es_str)
		exit_status = ft_atoi(es_str);
	clear_env(env);
	rl_clear_history();
	return (exit_status);
}
	//ft_putendl_fd("exit", STDERR_FILENO);
