/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:42:42 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/06 17:16:21 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void remove_char_string(char *str, char d)
{
	size_t index;
	size_t final_index;

	index = 0;
	final_index = 0;
	if (str == NULL)
		return;
	while (str[index])
	{
		if (str[index] != d)
			str[final_index++] = str[index];
		index++;
	}
	str[final_index] = '\0';
}

static void remove_quotes_loop(t_commands *commands)
{
	size_t	args_index;
	size_t	str_index;
	int		quote_type;

	args_index = 0;
	while (commands->arguments[args_index])
	{
		if (!ft_str_contains(commands->arguments[args_index], "'", 0) &&\
			!ft_str_contains(commands->arguments[args_index], "\"", 0))
		{
			args_index++;
			continue;
		}
		str_index = 0;
		quote_type = 0;
		while (commands->arguments[args_index][str_index])
		{
			char c = commands->arguments[args_index][str_index];
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

t_parsing_result post_parsing(t_minishell *shell)
{
	if (!build_command_from_tokens(shell))
		return (ERROR);
	remove_quotes(shell);
	ft_display_commands_list(shell->commands);
	ft_display_tokens(shell->parsing_cmd.tokens);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	return (SUCCESS);
}
