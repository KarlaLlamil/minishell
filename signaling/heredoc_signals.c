/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:55:45 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 17:35:43 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signaling.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

void	cancel_heredoc(int signal)
{
	if (signal == SIG_SIGINT)
		g_sigstat = SIG_SIGINT;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	set_heredoc_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, cancel_heredoc);
}
