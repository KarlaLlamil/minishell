/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:33:56 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 14:59:03 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signaling.h"
#include <signal.h>

t_sigstat	g_sigstat = SIG_BASE;

void	save_signal(int signal)
{
	g_sigstat = signal;
}

void	set_execution_signals(void)
{
	g_sigstat = SIG_BASE;
	signal(SIGQUIT, save_signal);
	signal(SIGINT, save_signal);
}

void	set_default_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
