/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_transformer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:46:17 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/22 15:17:00 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "memory_utils.h"
#include <stdlib.h>
#include <unistd.h>

static void	add_pwd_to_env(t_minishell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	env_map_replace_or_add(shell->env_map, "PWD", pwd);
	free(pwd);
}

t_env_map	*env_array_to_map(t_minishell *shell,
				t_env_map **env_map, char **envp)
{
	size_t		index;
	char		**split;
	char		*key;
	char		*value;
	t_env_map	*node;

	index = 0;
	while (envp[index])
	{
		key = NULL;
		value = NULL;
		split = ft_split(envp[index++], '=');
		if (!split)
			return (shell->is_running = 0, shell->env_map);
		if (split[0])
			key = split[0];
		if (split[1])
			value = split[1];
		node = ft_create_env_node(key, value, 1, 1);
		env_map_add_back(env_map, node, 0);
		ft_free_split(split);
	}
	add_pwd_to_env(shell);
	return (*env_map);
}

char	**env_map_to_array(t_env_map *env_map)
{
	char		**env_array;
	char		*tmp_key;
	size_t		index;
	size_t		env_map_size;
	t_env_map	*tmp;

	env_map_size = env_map_get_size(env_map);
	env_array = ft_calloc(env_map_size + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	index = 0;
	while (index < env_map_size)
	{
		tmp = env_map_find_node(env_map, env_map_get_key(env_map, index));
		if (tmp->has_equal)
		{
			tmp_key = ft_strjoin(tmp->key, "=");
			env_array[index] = ft_strjoin(tmp_key, tmp->value);
			free(tmp_key);
		}
		else
			env_array[index] = ft_strjoin(tmp->key, tmp->value);
		index++;
	}
	return (env_array);
}
