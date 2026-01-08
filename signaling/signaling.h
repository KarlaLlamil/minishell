/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:28:48 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/18 20:05:00 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALING_H
# define SIGNALING_H
# include <signal.h>

typedef enum signal_status
{
	SIG_BASE,
	SIG_SIGINT = SIGINT,
	SIG_SIGQUIT = SIGQUIT
}	t_sigstat;

extern t_sigstat	g_sigstat;

void	set_prompt_signals(void);
void	set_execution_signals(void);
void	set_default_signals(void);
void	set_heredoc_signals(void);
void	reset_prompt(int signal);
int		write_to_tty(char *str);

#endif
