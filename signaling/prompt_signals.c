/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:57:57 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 15:05:04 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signaling.h"
#include <signal.h>
#include <readline/readline.h>

void	reset_prompt(int signal)
{
	if (signal == SIG_SIGINT)
	{
		write_to_tty("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_prompt_signals(void)
{
	g_sigstat = SIG_BASE;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, reset_prompt);
}
