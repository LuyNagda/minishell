/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:32:59 by luynagda          #+#    #+#             */
/*   Updated: 2024/02/22 20:33:02 by luynagda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"
#include "put_utils.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>

t_boolean	process_space(t_minishell *shell, t_tokens *tmp, char *str)
{
	char	*space;

	if (tmp->previous)
		if (process_previous_token(tmp, str))
			return (_true);
	free(tmp->value);
	space = ft_strdup(" ");
	if (space == NULL)
		return (_true);
	tmp->value = space;
	tmp->type = _SPACE;
	treat_spaced_values(shell, tmp, str);
	free(str);
	return (_false);
}

void	process_expand(t_minishell *shell, t_tokens *tmp, char *value)
{
	char	*str;

	if (value == NULL)
		return ;
	str = ft_strdup(value);
	if (str == NULL)
		return ;
	if (ft_str_contains(str, " ", 0))
		if (process_space(shell, tmp, str))
			return ;
	delete_prev_token(shell, tmp);
	free(tmp->value);
	tmp->value = str;
	tmp->type = ENV_VALUE;
}

t_boolean	expand_status(t_minishell *shell, char **value)
{
	t_env_map	*env_finded;

	env_finded = env_map_find_node(shell->env_map, "?");
	if (!env_finded)
		*value = ft_strdup("0");
	else
		*value = ft_strdup(env_finded->value);
	if (!*value)
		return (_true);
	return (_false);
}

t_boolean	expand_normal(t_minishell *shell, t_tokens *tokens, char **value)
{
	char		*trim;
	t_env_map	*env_finded;

	env_finded = env_map_find_node(shell->env_map, tokens->value);
	if (env_finded == NULL)
	{
		*value = ft_strdup("");
		if (!*value)
			return (_true);
	}
	else
	{
		*value = ft_strdup(env_finded->value);
		if (!*value)
			return (_true);
		if (tokens->type != QUOTED)
		{
			trim = ft_strtrim(*value, " ");
			free(*value);
			*value = trim;
		}
	}
	return (_false);
}
