/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karlarod <karlarod@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:52:56 by karlarod          #+#    #+#             */
/*   Updated: 2025/11/20 05:30:51 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "tokens.h"
#include "envctl.h"
#include "libft.h"
#include <stdlib.h>
#include "expansion.h"

int	expand_args(t_command *cmd, t_hashtable env)
{
	int			i;
	t_expansion	expander;

	i = 0;
	while (i < cmd->n_args)
	{
		expander = (t_expansion){};
		is_quoted(cmd->arguments[i], &expander);
		expander.name = ft_strchr(cmd->arguments[i], '$');
		if (expander.name != NULL)
		{
			if (substitute_var_cmds(cmd->arguments[i], &expander, env) == 1)
				return (1);
			i = substitute_args(cmd, i, &expander);
			if (i == -1)
				return (1);
		}
		else
		{
			remove_quotes(cmd->arguments[i], &expander);
			++i;
		}
	}
	return (0);
}

int	substitute_file_name(t_list *redirs, t_expansion *expander, t_hashtable env)
{
	char	*file;

	file = ((t_redir *)redirs->content)->file;
	substitute_var_cmds(file, expander, env);
	if (expander->in_quotes == false || expander->name < expander->start_quotes
		|| expander->name > expander->end_quotes)
	{
		if (count_new_args(file) > 1)
		{
			ft_printf("%s: ambigous redirect", expander->name);
			free (expander->line);
			return (1);
		}
	}
	free(((t_redir *)redirs->content)->file);
	is_quoted(expander->line, expander);
	((t_redir *)redirs->content)->file = expander->line;
	return (0);
}

int	expand_redirs(t_list *redirs, t_hashtable env)
{
	t_expansion	expander;
	int			status;
	char		*file;

	while (redirs != NULL)
	{
		file = ((t_redir *)redirs->content)->file;
		if (file)
		{
			expander = (t_expansion){};
			is_quoted(file, &expander);
			expander.name = ft_strchr(file, '$');
			if (expander.name != NULL)
			{
				status = substitute_file_name(redirs, &expander, env);
				if (status == 1)
					return (1);
			}
			if (expander.in_quotes == true)
				remove_quotes(file, &expander);
		}
		redirs = redirs->next;
	}
	return (0);
}

int	expand_assignment(t_list *assignments, t_hashtable env)
{
	t_expansion		expander;
	t_assignment	*variable;

	while (assignments != NULL)
	{
		expander = (t_expansion){};
		variable = (t_assignment *)assignments->content;
		is_quoted(variable->value, &expander);
		expander.name = ft_strchr(variable->value, '$');
		if (expander.name != NULL)
		{
			if (substitute_var_cmds(variable->value, &expander, env) == 1)
				return (1);
			free(variable->value);
			is_quoted(expander.line, &expander);
			variable->value = expander.line;
		}
		if (expander.in_quotes == true)
			remove_quotes(variable->value, &expander);
		set_tmp_var(variable->name, variable->value, env);
		assignments = assignments->next;
	}
	return (0);
}

int	expand_cmd(t_command *cmd, t_hashtable env)
{
	t_list	*redirs;
	t_list	*assignments;

	redirs = cmd->redirs;
	assignments = cmd->assignments;
	if (cmd != NULL)
	{
		if (expand_args(cmd, env) == 1)
			return (1);
		if (expand_redirs(redirs, env) == 1)
			return (1);
		if (expand_assignment(assignments, env) == 1)
			return (1);
	}
	return (0);
}
