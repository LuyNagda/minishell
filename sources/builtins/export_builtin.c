/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:50 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/22 12:53:05 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>

void	exec_export_part(t_minishell *shell, t_commands *command)
{
	t_env_map	*node;
	char		**export;
	char		*key;
	char		*value;

	if (command->arguments[2])
	{
		key = ft_strtrim(command->arguments[1], "=");
		value = ft_strtrim(command->arguments[2], "\"");
		node = ft_create_env_node(key, value, 1, 0);
		env_map_add_back(&shell->env_map, node, 1);
		free(key);
		free(value);
		return ;
	}
	export = ft_split(command->arguments[1], '=');
	if (!export[1])
	{
		node = ft_create_env_node(export[0], "NULL", 0, 0);
		env_map_add_back(&shell->env_map, node, 1);
		ft_free_split(export);
		return ;
	}
	node = env_map_find_node(shell->env_map, export[0]);
	if (node != NULL)
	{
		env_map_replace(shell->env_map, export[0], export[1]);
		ft_free_split(export);
		return ;
	}
	node = ft_create_env_node(export[0], export[1], 1, 0);
	env_map_add_back(&shell->env_map, node, 1);
}

void	exec_export(t_minishell *shell, t_commands *command)
{
	t_env_map 	*node;

	env_map_replace_or_add(shell->env_map, "?", "0");
	if (command->arguments_amount == 1)
	{
		node = shell->env_map;
		while (node)
		{
			if (!ft_str_equals(node->key, "?"))
			{
				printf("declare -x %s", node->key);
				if (node->has_equal)
					printf("=\"%s\"", node->value);
				printf("\n");
			}
			node = node->next_node;
		}
		return ;
	}
	exec_export_part(shell, command);
}
