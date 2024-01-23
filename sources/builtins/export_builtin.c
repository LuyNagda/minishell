/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:50 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/23 17:46:27 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>

static char	**get_export_values(t_commands *command, int *i)
{
	char	**export;

	if (!(command->arguments[*i]))
		return (NULL);
	if (ft_str_contains(command->arguments[*i], "=",
		ft_strlen(command->arguments[*i]) - 1)
		&& ft_str_contains(command->arguments[*i + 1], "\"", 0))
	{
		export = (char **)malloc(sizeof(char *) * 3);
		export[0] = ft_strtrim(command->arguments[*i], "=");
		export[1] = ft_strtrim(command->arguments[*i + 1], "\"");
		export[2] = 0;
		*i = *i + 2;
	}
	else
	{
		export = ft_split(command->arguments[*i], '=');
		if (!export[1])
		{
			ft_free_split(export);
			export = (char **)malloc(sizeof(char *) * 3);
			export[0] = ft_strdup(command->arguments[*i]);
			export[1] = NULL;
			export[2] = 0;
		}
		*i = *i + 1;
	}
	return (export);
}

static int	export_if_no_equal(t_minishell *shell, char **export)
{
	t_env_map	*node;

	if (!export[1])
	{
		node = env_map_find_node(shell->env_map, export[0]);
		if (node != NULL)
		{
			env_map_replace(shell->env_map, export[0], export[1]);
			node->has_equal = 0;
			ft_free_split(export);
			return (1);
		}
		node = ft_create_env_node(export[0], "NULL", 0, 0);
		env_map_add_back(&shell->env_map, node, 0);
		ft_free_split(export);
		return (1);
	}
	return (0);
}

static void	exec_export_part(t_minishell *shell, t_commands *command)
{
	t_env_map	*node;
	char		**export;
	int			i;

	i = 1;
	while (i <= command->arguments_amount)
	{
		export = get_export_values(command, &i);
		if (!export)
			break ;
		if (export_if_no_equal(shell, export))
			continue ;
		node = env_map_find_node(shell->env_map, export[0]);
		if (node != NULL)
		{
			env_map_replace(shell->env_map, export[0], export[1]);
			node->has_equal = 1;
			ft_free_split(export);
			continue ;
		}
		node = ft_create_env_node(export[0], export[1], 1, 0);
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
		return ;
	}
	exec_export_part(shell, command);
}
