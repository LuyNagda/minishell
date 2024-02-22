/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:43:45 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/22 16:26:02 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "stdlib.h"

void	env_map_init(t_minishell *shell)
{
	t_env_map	*node;

	shell->env_map = NULL;
	node = ft_create_env_node("?", "0", _true, _true);
	if (node)
		env_map_add_back(&shell->env_map, node, 1);
}

t_env_map	*ft_create_env_node(char *key, char *value,
				int has_equals, int is_system)
{
	t_env_map	*new_node;

	new_node = malloc(sizeof(t_env_map));
	if (!new_node)
		return (NULL);
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->has_equal = has_equals;
	new_node->is_system = is_system;
	new_node->is_immutable = 0;
	new_node->next_node = NULL;
	return (new_node);
}

void	env_map_flush(t_env_map *env_map)
{
	t_env_map	*tmp;

	while (env_map)
	{
		tmp = env_map->next_node;
		if (env_map->key)
			free(env_map->key);
		if (env_map->value)
		{
			free(env_map->value);
			env_map->value = NULL;
		}
		free(env_map);
		env_map = tmp;
	}
}
