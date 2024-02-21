/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:42:42 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/21 12:47:53 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "string_utils.h"

static void	remove_char_string(char *str, char d)
{
	size_t	index;
	size_t	final_index;

	index = 0;
	final_index = 0;
	if (str == NULL)
		return ;
	while (str[index])
	{
		if (str[index] != d)
			str[final_index++] = str[index];
		index++;
	}
	str[final_index] = '\0';
}

static void	remove_quotes_loop(t_commands *commands)
{
	size_t	args_index;
	size_t	str_index;
	int		quote_type;
	char	c;

	args_index = 0;
	while (commands->arguments[args_index])
	{
		if (!ft_str_contains(commands->arguments[args_index], "'", 0) && \
			!ft_str_contains(commands->arguments[args_index], "\"", 0))
		{
			args_index++;
			continue ;
		}
		str_index = 0;
		quote_type = 0;
		while (commands->arguments[args_index][str_index])
		{
			c = commands->arguments[args_index][str_index];
			if (c == '\'')
			{
				if (quote_type == 0)
					quote_type = 1;
				else if (quote_type == 1)
					quote_type = 0;
				if (quote_type == 1 || quote_type == 0)
					commands->arguments[args_index][str_index] = '\a';
			}
			else if (c == '\"')
			{
				if (quote_type == 0)
					quote_type = 2;
				else if (quote_type == 2)
					quote_type = 0;
				if (quote_type == 2 || quote_type == 0)
					commands->arguments[args_index][str_index] = '\a';
			}
			str_index++;
		}
		remove_char_string(commands->arguments[args_index], '\a');
		args_index++;
	}
}

static t_parsing_result	remove_quotes(t_minishell *shell)
{
	t_commands	*commands;

	commands = shell->commands;
	while (commands)
	{
		remove_quotes_loop(commands);
		commands = commands->next_node;
	}
	return (SUCCESS);
}

static t_boolean	is_special_token(t_tokens *token)
{
	return (token->type == PIPE || \
		token->type == REDIRECT_IN || \
		token->type == REDIRECT_OUT || \
		token->type == REDIRECT_IN_DOUBLE || \
		token->type == REDIRECT_OUT_DOUBLE);
}

static t_boolean	specials_is_valid(t_minishell *shell)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		if (is_special_token(tmp))
		{
			if (tmp->next == NULL)
				return (_false);
			tmp2 = tmp->next;
			while (tmp2->type == _SPACE)
				tmp2 = tmp2->next;
			if (is_special_token(tmp2))
				return (_false);
		}
		tmp = tmp->next;
	}
	return (_true);
}

t_parsing_result	post_parsing(t_minishell *shell)
{
	t_tokens	*end_token;
	char		*str;

	str = ft_strdup("|");
	if (!str)
		return (ERROR);
	end_token = ft_create_token(str, PIPE);
	if (!end_token)
		return (free(str), ERROR);
	if (!specials_is_valid(shell))
		return (printf("%s\n", shell->messages.other_input_error), \
			ft_free_token(end_token), INVALID_INPUT);
	ft_add_back_token(&shell->parsing_cmd.tokens, end_token);
	if (!build_command_from_tokens(shell))
		return (ft_delete_token(&shell->parsing_cmd.tokens, end_token), ERROR);
	remove_quotes(shell);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	ft_delete_token(&shell->parsing_cmd.tokens, end_token);
	return (SUCCESS);
}
