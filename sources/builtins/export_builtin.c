/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:50 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/24 14:53:09 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>

static void	export_vars(t_minishell *shell, t_commands *command)
{
	t_env_map	*node;
	char		**export;
	int			i;
	int			has_equal;

	i = 1;
	has_equal = 0;
	while (i <= command->arguments_amount)
	{
		export = get_export_values(command, &i, &has_equal);
		if (!export)
			break ;
		node = env_map_find_node(shell->env_map, export[0]);
		if (node != NULL)
		{
			env_map_replace(shell->env_map, export[0], export[1]);
			node->has_equal = has_equal;
			ft_free_split(export);
			continue ;
		}
		node = ft_create_env_node(export[0], export[1], has_equal, 0);
		env_map_add_back(&shell->env_map, node, 0);
		ft_free_split(export);
	}
}

void	exec_export(t_minishell *shell, t_commands *command)
{
	t_env_map	*node;
	t_env_map	*duplicate;

	env_map_replace_or_add(shell->env_map, "?", "0");
	if (command->arguments_amount == 1)
	{
		duplicate = duplicate_list(shell->env_map);
		node = merge_sort(duplicate);
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
		free_duplicate_env(duplicate);
		return ;
	}
	export_vars(shell, command);
}
