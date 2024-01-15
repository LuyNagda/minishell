/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:26:51 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/15 12:26:25 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "memory_utils.h"
#include "stdlib.h"

t_commands *build_command_from_tokens(t_minishell *shell)
{
	t_tokens *tmp;
	t_commands *builded;
	size_t arg_index;
	char **args;

	tmp = shell->parsing_cmd.tokens;
	args = NULL;
	while (tmp)
	{
		if (!args)
		{
			arg_index = 0;
			args = ft_calloc((ft_get_tokens_amount(shell->parsing_cmd.tokens) + 1), sizeof(char *));
			continue;
		}
		if (tmp->type == SPACE)
		{
			tmp = tmp->next;
			continue;
		}
		if (tmp->value && tmp->type != PIPE)
			args[arg_index++] = ft_strdup(tmp->value);
		if (tmp->type == PIPE)
		{
			builded = ft_command_new_node(args);
			if (!builded)
				return (ft_free_split(args), NULL);
			ft_add_command(&shell->commands, builded);
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
		free(list);
		list = tmp;
	}
}
