/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:43:18 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/23 19:59:57 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_map	*env_map_find_node(t_env_map *env_map, char *key)
{
	t_env_map	*tmp;

	if (!env_map)
		return (NULL);
	tmp = env_map;
	while (tmp)
	{
		if (ft_str_equals(tmp->key, key))
			return (tmp);
		tmp = tmp->next_node;
	}
	return (NULL);
}

t_env_map *env_map_get_from_value(t_env_map *env_map, char *value)
{
	t_env_map	*tmp;

	if (!env_map)
		return (NULL);
	tmp = env_map;
	while (tmp)
	{
		if (ft_str_equals(tmp->value, value))
			return (tmp);
		tmp = tmp->next_node;
	}
	return (NULL);
}


size_t	env_map_get_size(t_env_map *env_map)
{
	size_t	length;

	length = 0;
	while (env_map)
	{
		length++;
		env_map = env_map->next_node;
	}
	return (length);
}

char	*env_map_get_key(t_env_map *env_map, size_t node_pos)
{
	size_t	i;

	i = 0;
	while (i < node_pos)
	{
		if (!env_map->next_node)
			return (NULL);
		env_map = env_map->next_node;
		i++;
	}
	return (env_map->key);
}
