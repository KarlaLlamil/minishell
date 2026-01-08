/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:23:39 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 14:01:30 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envctl.h"
#include "libft.h"
#include <unistd.h>
#include <stdbool.h>

static char	**get_flags(char **cmd_args, char *flag_list, int *flag_buff)
{
	char			**text;
	unsigned int	i;
	unsigned int	flag_no;

	*flag_buff = 0;
	text = cmd_args + 1;
	while (*text && (*text)[0] == '-' && ft_strchr(flag_list, (*text)[1]))
	{
		i = 1;
		while ((*text)[i] && ft_strchr(flag_list, (*text)[i]))
		{
			flag_no = ft_strchr(flag_list, (*text)[i]) - flag_list;
			*flag_buff = *flag_buff | (1 << flag_no);
			i++;
		}
		if ((*text)[i])
		{
			*flag_buff = 0;
			text = cmd_args + 1;
			break ;
		}
		text++;
	}
	return (text);
}

int	echo_cmd(char **cmd_args, t_hashtable env)
{
	char	**text;
	int		flag_n;

	flag_n = 0;
	text = get_flags(cmd_args, "n", &flag_n);
	while (*text)
	{
		ft_putstr_fd(*text, STDOUT_FILENO);
		text++;
		if (*text)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag_n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
	do_nothing_builtins(cmd_args, env);
}
