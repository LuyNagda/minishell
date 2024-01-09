/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:26:51 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 20:19:51 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../dependencies/libft/.includes/string_utils.h"
#include "stdlib.h"

t_commands	*ft_command_list_init()
{
	t_commands	*list;

	list = malloc(sizeof(t_commands));
	if (!list)
		return (NULL);
	list->raw_command = NULL;
	list->command_name = NULL;
	list->arguments = NULL;
	list->arguments_amount = 0;
	list->mixed = NULL;
	list->has_already_executed = _false;
	list->position = 0;
	list->next_node = NULL;
	list->error_during_creation = _false;
	return (list);
}

t_commands	*ft_create_command_node(char *cmd)
{
	t_commands	*command;
	char		**splitted;

	command = malloc(sizeof(t_commands));
	if (!command)
		return (NULL);
	command->raw_command = ft_strdup(cmd);
	if (!command->raw_command)
		return (command->error_during_creation = _true, command);
	splitted = ft_split(cmd, ' ');
	if (!splitted)
		return (NULL);
	command->command_name = ft_strdup(splitted[0]);
	if (!command->command_name)
		return (command->error_during_creation = _true, ft_free_split(splitted), command);
	command->arguments = ft_memcpy_array(splitted, 1);
	if (!command->arguments)
		return (command->error_during_creation = _true, ft_free_split(splitted), command);
	command->mixed = ft_memcpy_array(splitted, 0);
	if (!command->mixed)
		return (command->error_during_creation = _true, ft_free_split(splitted), command);
	ft_free_split(splitted);
	command->arguments_amount = ft_str_tab_len(command->arguments);
	command->has_already_executed = _false;
	command->error_during_creation = _false;
	return (command);
}

void	ft_flush_command_list(t_commands *list)
{
	t_commands	*tmp;

	while (list)
	{
		tmp = list->next_node;
		if (list->raw_command)
			free(list->raw_command);
		if (list->command_name)
			free(list->command_name);
		if (list->arguments)
			ft_free_split(list->arguments);
		if (list->mixed)
			ft_free_split(list->mixed);
		free(list);
		list = tmp;
	}
}
