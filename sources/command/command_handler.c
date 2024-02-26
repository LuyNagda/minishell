/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:26:42 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/26 18:01:34 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "memory_utils.h"

size_t	ft_get_numbers_of_commands(t_commands *commands_list)
{
	size_t	length;

	length = 0;
	while (commands_list)
	{
		length++;
		commands_list = commands_list->next_node;
	}
	return (length);
}

size_t	ft_get_arguments_amount(t_commands *command)
{
	size_t	i;

	i = 0;
	while (command->arguments[i])
		i++;
	return (i);
}

t_commands	*ft_command_new_node(char **args)
{
	t_commands	*command;

	command = ft_calloc(1, sizeof(t_commands));
	if (!command)
		return (NULL);
	command->raw_command = build_str_from_array(args);
	if (!command->raw_command)
		return (command);
	command->arguments = args;
	command->arguments_amount = ft_str_tab_len(args);
	command->has_already_executed = _false;
	command->position = 0;
	command->next_node = NULL;
	command->error_during_creation = _false;
	command->is_builtin = is_builtins(command);
	command->args_quoted = ft_fill_args_quotes(args);
	return (command);
}

t_commands	*ft_add_command(t_minishell *shell, t_commands *new_node)
{
	t_commands	*tmp;

	if (!shell->commands)
	{
		shell->commands = new_node;
		return (new_node);
	}
	tmp = shell->commands;
	while (tmp->next_node)
		tmp = tmp->next_node;
	new_node->position = ft_get_numbers_of_commands(shell->commands);
	tmp->next_node = new_node;
	return (new_node);
}
