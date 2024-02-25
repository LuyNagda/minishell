/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:33:04 by luynagda          #+#    #+#             */
/*   Updated: 2024/02/25 16:29:54 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "minishell.h"
#include <stdlib.h>

static void	treat_spaced_values(t_minishell *shell, \
t_tokens *current, char *value)
{
	char		**split;
	char		*str;
	t_tokens	*new;
	size_t		split_size;

	if (!ft_str_contains(value, " ", 0))
		return ;
	split = ft_split(value, ' ');
	if (split == NULL)
		return ;
	split_size = ft_str_tab_len(split) -1;
	while (split[split_size] != NULL && split_size > 0)
	{
		str = ft_strdup(split[split_size]);
		if (str == NULL)
			continue ;
		new = ft_create_token(str, ENV_VALUE);
		if (new == NULL)
			continue ;
		add_token_after(&shell->parsing_cmd.tokens, new, current);
		add_space_token(shell, new);
		split_size--;
	}
	ft_free_split(split);
}

static int	contains_valid_key(t_minishell *shell, t_tokens *token)
{
	t_tokens	*previous;
	size_t		nb_dollars;
	size_t		token_pos;
	char		*rebuilded_string;

	if (token->type != WORD && token->type != QUOTED && token->type != INTERO)
		return (_false);
	nb_dollars = 0;
	previous = token->previous;
	while (previous && previous->value && \
	previous->value[0] == '$' && ++nb_dollars)
		previous = previous->previous;
	if (nb_dollars != 1)
		return (_false);
	rebuilded_string = rebuild_string_from_token(shell);
	if (rebuilded_string == NULL)
		return (_false);
	token_pos = get_current_token_pos(token);
	if (!quotes_is_valid(rebuilded_string, \
	get_index_from_token(shell, token_pos)))
		return (free(rebuilded_string), _false);
	return (free(rebuilded_string), _true);
}

static void	process_expand_with_space(t_minishell *shell, \
t_tokens *tmp, char *str)
{
	char	**split;
	char	*dup;
	char	*space;

	if (tmp->previous)
	{
		free(tmp->previous->value);
		tmp->previous->value = NULL;
		split = ft_split(str, ' ');
		if (split == NULL)
			return ;
		dup = ft_strdup(split[0]);
		if (dup == NULL)
			return ;
		tmp->previous->value = dup;
		tmp->previous->type = ENV_VALUE;
		ft_free_split(split);
	}
	free(tmp->value);
	space = ft_strdup(" ");
	if (space == NULL)
		return ;
	tmp->value = space;
	tmp->type = _SPACE;
	treat_spaced_values(shell, tmp, str);
}

static void	process_expand(t_minishell *shell, t_tokens *tmp, char *value)
{
	char	*str;

	if (value == NULL)
		return ;
	str = ft_strdup(value);
	if (str == NULL)
		return ;
	if (ft_str_contains(str, " ", 0))
	{
		process_expand_with_space(shell, tmp, str);
		free(str);
	}
	else
	{
		delete_prev_token(shell, tmp);
		free(tmp->value);
		tmp->value = str;
		tmp->type = ENV_VALUE;
	}
}

void	treat_variable_keys(t_minishell *shell)
{
	t_tokens	*tokens;
	char		*value;

	tokens = shell->parsing_cmd.tokens;
	value = NULL;
	while (tokens)
	{
		if (!contains_valid_key(shell, tokens))
		{
			tokens = tokens->next;
			continue ;
		}
		if (ft_str_starts_with(tokens->value, "?"))
			value = get_status_value(shell, value);
		else
			value = get_normal_value(shell, tokens, value);
		if (value == NULL)
			return ;
		process_expand(shell, tokens, value);
		free_value(value);
		tokens = tokens->next;
	}
}
