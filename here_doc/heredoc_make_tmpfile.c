/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_make_tmpfile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 02:00:31 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 17:11:10 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static bool	random_name(char *name, char *char_set)
{
	int		fd;
	char	random_data[9];
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (false);
	i = read(fd, random_data, 9);
	if (i < 0)
	{
		close(fd);
		return (false);
	}
	name[i] = '\0';
	while (i > 0)
	{
		--i;
		name[i] = char_set[random_data[i] % (sizeof (char_set) - 1)];
	}
	close (fd);
	return (true);
}

bool	ft_mkstmp(t_heredoc *heredoc)
{
	char	*char_set;
	char	name[10];

	char_set = ft_strdup(VALID_NAME);
	if (char_set == NULL)
		return (false);
	if (random_name(name, char_set) == false)
	{
		free(char_set);
		return (false);
	}
	heredoc->file_name = ft_strjoin("/tmp/here_doc_", name);
	free(char_set);
	if (heredoc->file_name == NULL)
		return (false);
	heredoc->fd = open(heredoc->file_name, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (heredoc->fd < 0)
		return (free(heredoc->file_name), false);
	return (true);
}
