/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_tty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 02:45:02 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 14:59:41 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int	write_to_tty(char *str)
{
	int	ttyfd;

	ttyfd = open("/dev/tty", O_RDWR);
	ft_putstr_fd(str, ttyfd);
	close(ttyfd);
	return (0);
}
