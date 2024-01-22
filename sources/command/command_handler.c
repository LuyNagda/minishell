/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:26:42 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/22 15:56:02 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "memory_utils.h"
#include "ft_printf.h"
#include "stdlib.h"


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

t_commands	*ft_get_command_from_pos(t_commands *command_list, size_t command_node_pos)
{
	size_t	i;

	i = 0;
	while (i < command_node_pos)
	{
		if (!command_list->next_node)
			return (NULL);
		command_list = command_list->next_node;
		i++;
	}
	return (command_list);
}

t_commands	*ft_command_init()
{
	t_commands	*list;

	list = malloc(sizeof(t_commands));
	if (!list)
		return (NULL);
	list->raw_command = NULL;
	list->arguments = NULL;
	list->arguments_amount = 0;
	list->has_already_executed = _false;
	list->position = 0;
	list->next_node = NULL;
	list->error_during_creation = _false;
	list->input_fd = 0;
	list->output_fd = 0;
	list->is_builtin = 0;
	list->here_doc = NULL;
	return (list);
}

t_commands	*ft_command_new_node(t_env_map *map, char **args)
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
	if (is_builtins(command))
		command->path = ft_strdup("builtin");
	else
		command->path = find_command(map, args[0]);
	return (command);
}

t_commands	*ft_add_command(t_commands **commands, t_commands *new_node)
{
	t_commands *tmp = *commands;

	if (tmp == NULL || tmp->arguments == NULL)
	{
		*commands = new_node;
		return (new_node);
	}
	while (tmp->next_node)
		tmp = tmp->next_node;
	new_node->position = ft_get_numbers_of_commands(*commands);
	tmp->next_node = new_node;
	return (new_node);
}