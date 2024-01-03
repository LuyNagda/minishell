/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:27:00 by jbadaire          #+#    #+#             */
/*   Updated: 2023/11/29 14:10:39 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"

char **convert_path_to_array(t_env_map *env_map)
{
	char		**path_array;
	t_env_map	*path;

	path = env_map_find_node(env_map, "PATH");
	path_array = ft_split(path->value, ':');
	return (path_array);
}