/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:43:18 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/23 17:14:59 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "stdlib.h"
#include <stdio.h>

t_env_map	*env_map_add_back(t_env_map **env_map,
			t_env_map *new_node, int is_immutable)
{
	t_env_map	*tmp;

	tmp = *env_map;
	if (is_immutable)
		new_node->is_immutable = 1;
	if (tmp == NULL)
	{
		*env_map = new_node;
		return (*env_map);
	}
	while (tmp->next_node)
		tmp = tmp->next_node;
	tmp->next_node = new_node;
	return (*env_map);
}

t_env_map	*env_map_remove_from_key(t_env_map *env_map, char *key)
{
	t_env_map	*previous_node;
	t_env_map	*current_node;

	if (!env_map || !key)
		return (NULL);
	current_node = env_map;
	while (current_node)
	{
		if (ft_str_equals(current_node->key, key))
		{
			if (current_node->is_immutable)
				return (NULL);
			if (previous_node)
				previous_node->next_node = current_node->next_node;
			else
				env_map = current_node->next_node;
			if (current_node->value)
				free(current_node->value);
			if (current_node->key)
				free(current_node->key);
			return (free(current_node), env_map);
		}
		previous_node = current_node;
		current_node = current_node->next_node;
	}
	return (env_map);
}

t_env_map	*env_map_replace(t_env_map *env_map, char *key, char *value)
{
	t_env_map	*tmp;

	if (!env_map)
		return (NULL);
	tmp = env_map;
	while (tmp)
	{
		if (ft_str_equals(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (env_map);
		}
		tmp = tmp->next_node;
	}
	return (NULL);
}

t_env_map	*env_map_replace_or_add(t_env_map *env_map, char *key, char *value)
{
	t_env_map	*tmp;
	t_env_map	*node;

	if (!env_map)
		return (NULL);
	tmp = env_map_replace(env_map, key, value);
	if (tmp == NULL)
	{
		node = ft_create_env_node(key, value, 1, 0);
		if (!node)
			return (NULL);
		env_map_add_back(&env_map, node, 1);
		return (env_map);
	}
	return (tmp);
}
