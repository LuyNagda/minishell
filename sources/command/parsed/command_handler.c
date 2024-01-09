/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:26:42 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 19:47:55 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <stdlib.h>

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
	tmp->next_node = new_node;
	return (*commands);
}

void	*ft_populate_command_list(t_minishell *shell)
{
	char	*command;

	shell->commands = ft_command_list_init();
	if (!shell->commands)
		return (NULL);
	ft_concat_tokens(shell, _false);
	while (shell->parsing_cmd.latest_command != NULL)
	{
		if (!ft_quote_is_closed(shell->parsing_cmd.latest_command))
			ft_concat_quoted_pipes(shell, 0);
		ft_post_command(shell);
		command = shell->parsing_cmd.latest_command;
		if (!ft_add_command(&shell->commands, ft_create_command_node(command)))
		{
			free(command);
			shell->parsing_cmd.latest_command = NULL;
			ft_concat_tokens(shell, _false);
			break;
		}
		free(command);
		shell->parsing_cmd.latest_command = NULL;
		ft_concat_tokens(shell, _false);
	}
}