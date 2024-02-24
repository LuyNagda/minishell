/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_transformer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:46:17 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/24 11:06:12 by marvin           ###   ########.fr       */
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

static int	ft_fill_env(void **mlc, char const *text, int mlc_index)
{
	int	index;

	index = 0;
	while (text[index])
	{
		((char *)mlc)[mlc_index] = text[index];
		index++;
		mlc_index++;
	}
	return (mlc_index);
}

static char	*ft_strjoin_env(char const *s1, char const *s2)
{
	void	*mlc;
	int		size;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	mlc = malloc(sizeof(char ) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!mlc)
		return (NULL);
	size = ft_fill_env(mlc, s1, 0);
	size = ft_fill_env(mlc, s2, size);
	((char *) mlc)[size] = '\0';
	return ((char *) mlc);
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
			tmp_key = ft_strjoin_env(tmp->key, "=");
			env_array[index] = ft_strjoin_env(tmp->key, tmp->value);
			free(tmp_key);
		}
		else
			env_array[index] = ft_strjoin_env(tmp->key, tmp->value);
		index++;
	}
	return (env_array);
}
