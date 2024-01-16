/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:27:00 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/16 13:57:10 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

char **convert_path_to_array(t_env_map *env_map)
{
	char **path_array;
	t_env_map *path;

	path = env_map_find_node(env_map, "PATH");
	if (path == NULL)
		return (NULL);
	path_array = ft_split(path->value, ':');
	return (path_array);
}

char *find_command(char *command, char **path_array)
{
	int i;
	char *path;
	char *temp;

	i = 0;
	path = NULL;
	if (access(command, F_OK) == 0 && access(command, X_OK) == 0)
		return (ft_strdup(command));
	while (path_array[i])
	{
		temp = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(temp, command);
		free(temp);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
