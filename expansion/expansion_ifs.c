/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_ifs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 04:06:03 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 04:52:50 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include <stdlib.h>
#include "expansion.h"

int	count_new_args(char *new)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	if (new == NULL)
		return (count);
	while (*new != '\0')
	{
		if (in_word == false && ft_strchr(IFS, *new) == NULL)
		{
			++count;
			in_word = true;
		}
		if (in_word == true && ft_strchr(IFS, *new) != NULL)
			in_word = false;
		++new;
	}
	return (count);
}

int	insert_arguments(t_command *cmd, char **args, int *indx, char *new)
{
	int		i;
	int		len;

	i = 0;
	while (i < (indx[1] + cmd->n_args - 1))
	{
		len = 0;
		if (i < indx[0])
			args[i] = cmd->arguments[i];
		else if (i < indx[0] + indx[1])
		{
			while (ft_strchr(IFS, new[len]) == NULL)
				++len;
			args[i] = ft_substr(new, 0, len);
			if (args[i] == NULL)
				return (1);
			while (new[len] != '\0' && ft_strchr(IFS, new[len]))
				++len;
			new = new + len;
		}
		else
			args[i] = cmd->arguments[i - indx[1] + 1];
		++i;
	}
	return (0);
}

int	realloc_arguments(t_command *cmd, int arg_indx, char *new)
{
	char	**args;
	int		indx[2];

	indx[0] = arg_indx;
	indx[1] = count_new_args(new);
	args = malloc((sizeof(char *)) * (indx[1] + cmd->n_args));
	if (args == NULL)
		return (-1);
	if (insert_arguments(cmd, args, indx, new) == 1)
	{
		free(new);
		del_args(args);
		return (-1);
	}
	args[indx[1] + cmd->n_args - 1] = NULL;
	cmd->n_args = indx[1] + cmd->n_args - 1;
	free(cmd->arguments[arg_indx]);
	free (cmd->arguments);
	free(new);
	cmd->arguments = args;
	return (indx[1]);
}

int	substitute_args(t_command *cmd, int i, t_expansion *expander)
{
	int	n;
	int	export;

	export = ft_strncmp("export", cmd->arguments[0], -1);
	if (expander->in_quotes == true || export == 0)
	{
		free(cmd->arguments[i]);
		is_quoted(expander->line, expander);
		cmd->arguments[i] = expander->line;
		remove_quotes(cmd->arguments[i], expander);
		++i;
	}
	else
	{
		n = realloc_arguments(cmd, i, expander->line);
		if (n == -1)
			return (-1);
		i = i + n;
	}
	return (i);
}
