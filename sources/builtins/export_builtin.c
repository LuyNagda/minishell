/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:50 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/16 15:09:02 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "string_utils.h"

void	exec_export_part(t_minishell *shell, t_commands *command)
{
	t_env_map	*node;
	char		**export;

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

	if (command->arguments_amount == 1)
	{
		node = shell->env_map;
		while (node)
		{
			ft_printf("declare -x %s", node->key);
			if (node->has_equal)
				ft_printf("=\"%s\"", node->value);
			ft_printf("\n");
			node = node->next_node;
		}
		return ;
	}
	exec_export_part(shell, command);
}
