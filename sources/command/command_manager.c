/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:26:51 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/26 18:01:52 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "memory_utils.h"
#include "stdlib.h"

static char	**init_args(t_minishell *shell, char **args, size_t *arg_index)
{
	if (!args)
	{
		*arg_index = 0;
		args = ft_calloc(\
			(ft_get_tokens_amount(shell->parsing_cmd.tokens) + 1), \
			sizeof(char *));
		if (args == NULL)
			return (NULL);
	}
	return (args);
}

static char	**handle_non_pipe(t_tokens *tmp, char **args, size_t *arg_index)
{
	char	*dup;

	if (tmp->value && tmp->type != PIPE)
	{
		dup = ft_strdup(tmp->value);
		if (!dup)
		{
			ft_free_split(args);
			return (NULL);
		}
		args[(*arg_index)++] = dup;
	}
	return (args);
}

static char	**build_and_add_command(t_minishell *shell, char **args)
{
	t_commands	*builded;

	builded = ft_command_new_node(args);
	if (!builded)
		return (ft_free_split(args), NULL);
	ft_add_command(shell, builded);
	return (args);
}

t_commands	*build_command_loop(t_minishell *shell, char **args, size_t i)
{
	t_tokens	*tmp;

	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		args = init_args(shell, args, &i);
		if (args == NULL)
			return (NULL);
		if (tmp->type == _SPACE)
		{
			tmp = tmp->next;
			continue ;
		}
		args = handle_non_pipe(tmp, args, &i);
		if (args == NULL)
			return (NULL);
		if (tmp->type == PIPE)
		{
			if (build_and_add_command(shell, args) == NULL)
				return (NULL);
			args = NULL;
		}
		tmp = tmp->next;
	}
	return (shell->commands);
}

void	ft_flush_command_list(t_commands *list)
{
	t_commands	*tmp;

	while (list)
	{
		tmp = list->next_node;
		if (list->raw_command)
			free(list->raw_command);
		if (list->arguments)
			ft_free_split(list->arguments);
		if (list->path)
			free(list->path);
		if (list->args_quoted)
			free(list->args_quoted);
		free(list);
		list = tmp;
	}
}
