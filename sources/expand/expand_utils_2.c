/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:32:59 by luynagda          #+#    #+#             */
/*   Updated: 2024/02/24 12:36:48 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"
#include <stdlib.h>

char	*get_status_value(t_minishell *shell, char *value)
{
	t_env_map	*env_finded;

	env_finded = env_map_find_node(shell->env_map, "?");
	if (!env_finded)
		value = ft_strdup("0");
	else
		value = ft_strdup(env_finded->value);
	if (!value)
		return (NULL);
	return (value);
}

char	*get_normal_value(t_minishell *shell, \
t_tokens *tokens, char *value)
{
	t_env_map	*env_finded;
	char		*trim;

	env_finded = env_map_find_node(shell->env_map, tokens->value);
	if (env_finded == NULL)
	{
		value = ft_strdup("");
		if (!value)
			return (NULL);
		return (value);
	}
	value = ft_strdup(env_finded->value);
	if (!value)
		return (NULL);
	if (tokens->type != QUOTED)
	{
		trim = ft_strtrim(value, " ");
		free(value);
		value = trim;
	}
	return (value);
}

void	free_value(char *value)
{
	if (value)
	{
		free(value);
		value = NULL;
	}
}
