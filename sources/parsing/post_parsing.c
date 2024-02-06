/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:42:42 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/06 11:28:40 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string_utils.h>
#include "minishell.h"



static void remove_string_index(char *str, size_t index)
{
	char *without = ft_substr(str, 0, index);
	char *tmp = ft_strdup(str + index + 1);
	ft_strlcpy(str, without, index + 1);
	ft_strlcpy(str + index, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	free(without);
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
			if ((quote_type == 0 || quote_type == 1) && c == '\'')
			{
				if (quote_type == 1)
					quote_type = 0;
				else
					quote_type = 1;
				remove_string_index(commands->arguments[args_index], str_index);
			}
			else if ((quote_type == 0 || quote_type == 2) && c == '"')
			{
				if (quote_type == 2)
					quote_type = 0;
				else
					quote_type = 2;
				remove_string_index(commands->arguments[args_index], str_index);
			}
			str_index++;
		}
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
	ft_display_tokens(shell->parsing_cmd.tokens);
	ft_display_commands_list(shell->commands);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	return (SUCCESS);
}
