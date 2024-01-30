/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:42:42 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/30 17:41:09 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string_utils.h>
#include "minishell.h"

static t_boolean is_quoted(char *str, char quote)
{
	if (!str)
		return (_false);
	if (str[0] == quote)
		return (str[ft_strlen(str) - 1] == quote);
	return (_false);
}

static void remove_quotes_loop(t_commands *commands)
{
	size_t index;
	char *arg;
	char *tmp;

	index = 0;
	while (commands->arguments[index])
	{
		arg = commands->arguments[index];
		if (is_quoted(arg, '\'') || is_quoted(arg, '"'))
		{
			tmp = ft_substr(arg, 1, ft_strlen(arg) - 2);
			free(commands->arguments[index]);
			commands->arguments[index] = tmp;
		}
		index++;
	}
}

static t_parsing_result remove_quotes(t_minishell *shell)
{
	t_commands *commands;

	commands = shell->commands;
	while (commands)
	{
		remove_quotes_loop(commands);
		commands = commands->next_node;
	}
	return (SUCCESS);
}

static void merge_quotes(t_commands *commands)
{
	t_commands *tmp;
	size_t index;

	tmp = commands;
	while (tmp)
	{
		index = 0;
		while (tmp->arguments[index])
		{
			if (ft_str_equals(tmp->arguments[index], "\"") || ft_str_equals(tmp->arguments[index], "\'"))
			{

			}
			index++;
		}
		tmp = tmp->next_node;
	}
}

t_parsing_result post_parsing(t_minishell *shell)
{
	if (!build_command_from_tokens(shell))
		return (ERROR);
	//remove_quotes(shell);
	//ft_display_tokens(shell->parsing_cmd.tokens);
	//ft_display_commands_list(shell->commands);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	return (SUCCESS);
}
