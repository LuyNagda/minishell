/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:26:42 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 10:48:12 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_commands	*ft_add_command(t_commands **commands, t_commands *new_node)
{
	t_commands	*tmp;

	tmp = *commands;
	if (tmp->command_name == NULL)
	{
		*commands = new_node;
		return (*commands);
	}
	while (tmp->next_node)
		tmp = tmp->next_node;
	new_node->position = ft_get_numbers_of_commands(*commands);
	tmp->next_node = new_node;
	return (*commands);
}