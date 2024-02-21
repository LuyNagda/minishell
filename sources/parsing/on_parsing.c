/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:19:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/21 12:47:50 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "put_utils.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>

static void process_expand(t_minishell *shell, t_tokens *tmp, char *value);

static int	variable_in_string(const char *str, size_t index)
{
	int		inside_single_quotes;
	int		inside_double_quotes;
	char	current_quote;
	size_t	i;

	inside_single_quotes = 0;
	inside_double_quotes = 0;
	current_quote = 0;
	i = 0;
	while (i <= index)
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			if (!inside_double_quotes)
				current_quote = inside_single_quotes ? 0 : '\'';
			inside_single_quotes = !inside_single_quotes;
		}
		else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
		{
			if (!inside_single_quotes)
				current_quote = inside_double_quotes ? 0 : '"';
			inside_double_quotes = !inside_double_quotes;
		}
		i++;
	}
	return (current_quote == 0 || current_quote == '"');
}

static int	ft_has_only_whitespace_between_pipes(t_minishell *shell)
{
	t_tokens	*tmp;
	t_boolean	is_after_pipe;
	t_boolean	only_space;

	is_after_pipe = _false;
	only_space = _true;
	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (only_space && is_after_pipe)
				return (1);
			is_after_pipe = _true;
			only_space = _true;
		}
		else if (is_after_pipe)
		{
			if (tmp->type != _SPACE)
				only_space = _false;
		}
		tmp = tmp->next;
	}
	return (0);
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
	while (previous && previous->value
		&& previous->value[0] == '$' && ++nb_dollars)
		previous = previous->previous;
	if (nb_dollars != 1)
		return (_false);
	rebuilded_string = rebuild_string_from_token(shell);
	if (rebuilded_string == NULL)
		return (_false);
	token_pos = get_current_token_pos(token);
	if (!variable_in_string(rebuilded_string, get_index_from_token(shell, token_pos)))
		return (free(rebuilded_string), _false);
	return (free(rebuilded_string), _true);
}

static void add_space_token(t_minishell *shell, t_tokens *current)
{
	t_tokens *space_token;

	space_token = ft_create_token(ft_strdup(" "), _SPACE);
	if (space_token == NULL)
		return ;
	add_token_after(&shell->parsing_cmd.tokens, space_token, current);
}

static void delete_previous(t_minishell *shell, t_tokens *current)
{
	t_tokens *prev;

	if (current->previous)
	{
		prev = current->previous;
		free(prev->value);
		prev->value = NULL;
		ft_delete_token(&shell->parsing_cmd.tokens, prev);
	}
}

static void treat_spaced_values(t_minishell *shell, t_tokens *current, char *value)
{
	char **split;
	char *str;
	t_tokens *new;
	size_t split_size;

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
			continue;
		new = ft_create_token(str, ENV_VALUE);
		if (new == NULL)
			continue;
		add_token_after(&shell->parsing_cmd.tokens, new, current);
		add_space_token(shell, new);
		split_size--;
	}
	ft_free_split(split);
}

static void	treat_variable_keys(t_minishell *shell)
{
	t_tokens	*tmp;
	t_env_map	*env_finded;
	char		*value;
	char		*trim;

	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		if (!contains_valid_key(shell, tmp))
		{
			tmp = tmp->next;
			continue;
		}
		value = NULL;
		if (ft_str_starts_with(tmp->value, "?"))
			value = ft_strjoin(env_map_find_node(shell->env_map, "?")->value, tmp->value + 1);
		else
		{
			env_finded = env_map_find_node(shell->env_map, tmp->value);
			if (env_finded == NULL)
				value = ft_strdup("");
			else
			{
				value = ft_strdup(env_finded->value);
				if (tmp->type != QUOTED)
				{
					trim = ft_strtrim(value, " ");
					free(value);
					value = trim;
				}
			}
		}
		process_expand(shell, tmp, value);
		tmp = tmp->next;
	}
}

static void process_expand(t_minishell *shell, t_tokens *tmp, char *value)
{
	char **split;
	char *dup;

	if (value == NULL)
		return ;
	if (ft_str_contains(value, " ", 0))
	{
		if (tmp->previous)
		{
			free(tmp->previous->value);
			tmp->previous->value = NULL;
			split = ft_split(value, ' ');
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
		tmp->value = ft_strdup(" ");
		tmp->type = _SPACE;
		treat_spaced_values(shell, tmp, value);
	}
	else {
		delete_previous(shell, tmp);
		free(tmp->value);
		tmp->value = value;
		tmp->type = ENV_VALUE;
	}
	free(value);
}

static void	append_quoted(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp && tmp->next)
	{
		if ((tmp->type == QUOTED || tmp->type == SIMPLE_QUOTE ||\
			tmp->type == DOUBLE_QUOTE || tmp->type == WORD || tmp->type == ENV_VALUE) &&\
			(tmp->next->type == QUOTED || tmp->next->type == SIMPLE_QUOTE ||\
				tmp->next->type == DOUBLE_QUOTE || tmp->next->type == WORD || tmp->next->type == ENV_VALUE))
		{
			append_token(tmp, tmp->next);
			ft_delete_token(tokens, tmp->next);
			tmp = *tokens;
			continue ;
		}
		tmp = tmp->next;
	}
}

t_parsing_result	on_parse(t_minishell *shell)
{

	if (ft_has_only_whitespace_between_pipes(shell) != 0)
		return (ft_putstr_fd(shell->messages.whitepipe_error, 2), free(shell->sended_line), INVALID_INPUT);
	treat_variable_keys(shell);
	append_quoted(&shell->parsing_cmd.tokens);
	return (SUCCESS);
}
