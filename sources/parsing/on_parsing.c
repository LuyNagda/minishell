/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:19:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/30 16:59:48 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#include "minishell.h"
#include "put_utils.h"
#include "string_utils.h"
#include "ft_printf.h"
#include <stdlib.h>

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
			if (tmp->type != SPACE)
				only_space = _false;
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	contains_valid_key(t_minishell *shell, t_tokens *token)
{
	t_env_map	*map;
	t_tokens	*previous;
	size_t		nb_dollars;
	size_t		token_pos;
	char		*rebuilded_string;

	if (token->type != WORD && token->type != QUOTED)
		return (_false);
	nb_dollars = 0;
	previous = token->previous;
	while (previous && previous->value
		&& previous->value[0] == '$' && ++nb_dollars)
		previous = previous->previous;
	if (nb_dollars != 1)
		return (_false);
	rebuilded_string = rebuild_string_from_token(shell);
	token_pos = get_current_token_pos(token);
	if (!variable_in_string(rebuilded_string,
			get_index_from_token(shell, token_pos)))
		return (free(rebuilded_string), _false);
	map = env_map_find_node(shell->env_map, token->value);
	if (map == NULL)
		return (3);
	return (free(rebuilded_string), _true);
}

static void	treat_variable_keys(t_minishell *shell)
{
	t_tokens	*tmp;
	t_tokens	*prev;
	t_env_map	*env_finded;
	char		*value;

	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		if (contains_valid_key(shell, tmp))
		{
			env_finded = env_map_find_node(shell->env_map, tmp->value);
			if (env_finded == NULL)
				value = ft_strdup("");
			else
				value = ft_strdup(env_finded->value);
			prev = tmp->previous;
			free(prev->value);
			ft_delete_token(&shell->parsing_cmd.tokens, prev);
			free(tmp->value);
			tmp->value = value;
		}
		tmp = tmp->next;
	}
}

static void	append_quoted(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp && tmp->next)
	{
		if (tmp->type == QUOTED && tmp->next->type == QUOTED)
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
	t_tokens	*end_token;

	if (ft_has_only_whitespace_between_pipes(shell) != 0)
		return (ft_putstr_fd(shell->messages.whitepipe_error, 2), free(shell->sended_line), INVALID_INPUT);
	treat_variable_keys(shell);
	//ft_display_tokens(shell->parsing_cmd.tokens);
	append_quoted(&shell->parsing_cmd.tokens);
	//printf("\n\n\n");
	//ft_display_tokens(shell->parsing_cmd.tokens);
	end_token = ft_create_token(ft_strdup("|"), PIPE);
	if (!end_token)
		return (ERROR);
	ft_add_back_token(&shell->parsing_cmd.tokens, end_token);
//	shell->commands = ft_command_init();
//	if (!shell->commands)
//		return (ERROR);
	return (SUCCESS);
}
