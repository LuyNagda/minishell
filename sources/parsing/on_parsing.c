/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:19:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 17:03:07 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/put_utils.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include <stdlib.h>

/**
 * @brief Checks if a variable in a string is not within single quotes.
 *
 * This function determines whether a variable in a string, indicated by the
 * given index, is not within single quotes. It considers escaped quotes and
 * tracks the current quote status to make the decision.
 *
 * @param str The input string.
 * @param index The index of the variable in the string.
 * @return 1 if the variable is not within single quotes, 0 otherwise.
 */
static int is_variable_in_string(const char *str, size_t index)
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

static t_boolean ft_token_is_in_expendable_quote(t_minishell *shell, char *rebuilded_string, size_t token_pos)
{
	size_t len = get_index_from_token(shell, token_pos);
	return (is_variable_in_string(rebuilded_string, len));
}

static int ft_has_only_whitespace_between_pipes(t_minishell *shell)
{
	t_tokens *tmp;
	t_boolean is_after_pipe;
	t_boolean only_space;

	is_after_pipe = _false;
	only_space = _true;
	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (only_space && is_after_pipe)
				return 1;
			is_after_pipe = _true;
			only_space = _true;
		} else if (is_after_pipe)
		{
			if (tmp->type != SPACE)
				only_space = _false;
		}
		tmp = tmp->next;
	}
	return 0;
}

static t_boolean contains_valid_key(t_minishell *shell, t_tokens *token)
{
	t_env_map *map;
	t_tokens *previous;
	size_t nb_dollars;
	size_t token_pos;
	char *rebuilded_string;

	if (token->type != WORD)
		return (_false);
	map = env_map_find_node(shell->env_map, token->value);
	if (map == NULL)
		return (_false);
	nb_dollars = 0;
	previous = token->previous;
	while (previous && previous->value && previous->value[0] == '$' && ++nb_dollars)
		previous = previous->previous;
	if (nb_dollars != 1)
		return (_false);
	rebuilded_string = rebuild_string_from_token(shell);
	token_pos = get_current_token_pos(token);
	if (!ft_token_is_in_expendable_quote(shell, rebuilded_string, token_pos))
		return (free(rebuilded_string), _false);
	return (free(rebuilded_string), _true);
}

static void treat_variable_keys(t_minishell *shell)
{
	t_tokens *tmp;
	t_tokens *prev;
	t_env_map *env_finded;

	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		if (contains_valid_key(shell, tmp))
		{
			env_finded = env_map_find_node(shell->env_map, tmp->value);
			if (env_finded == NULL)
				continue;
			prev = tmp->previous;
			free(prev->value);
			prev->value = "";
			free(tmp->value);
			tmp->value = env_finded->value;
		}
		tmp = tmp->next;
	}
}

t_parsing_result on_parse(t_minishell *shell)
{
	if (ft_has_only_whitespace_between_pipes(shell) != 0)
		return (ft_putstr_fd(shell->messages.whitepipe_error, 2), free(shell->sended_line), INVALID_INPUT);
	treat_variable_keys(shell);
	ft_display_tokens(shell->parsing_cmd.tokens);

	//TODO: Build t_command
	return (SUCCESS);
}