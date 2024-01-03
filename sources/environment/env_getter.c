/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:43:18 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/18 13:34:48 by jbadaire         ###   ########.fr       */
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