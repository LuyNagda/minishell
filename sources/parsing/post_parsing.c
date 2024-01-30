/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:42:42 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/30 14:59:32 by jbadaire         ###   ########.fr       */
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
		return (str[ft_strlen(str) -1] == quote);
	return (_false);
}

static t_parsing_result	remove_quotes(t_minishell *shell)
{
	size_t		index;
	t_commands	*commands;
	char		*tmp;
	char		*arg;

	commands = shell->commands;
	while (commands)
	{
		index = 0;
		commands->args_quoted = malloc(sizeof (int) * commands->arguments_amount);
		if (!commands->args_quoted)
			return (ERROR);
		while (commands->arguments[index])
		{
			arg = commands->arguments[index];
			commands->args_quoted[index] = 0;
			if (is_quoted(arg, '\'') || is_quoted(arg, '"'))
			{
				tmp = ft_substr(arg, 1, ft_strlen(arg) - 2);
				free(commands->arguments[index]);
				commands->arguments[index] = tmp;
			}
			if (is_quoted(arg, '\''))
				commands->args_quoted[index] = 1;
			else if (is_quoted(arg, '"'))
				commands->args_quoted[index] = 2;
			index++;
		}
		commands = commands->next_node;
	}
	return (SUCCESS);
}

t_parsing_result	post_parsing(t_minishell *shell)
{
	if (!build_command_from_tokens(shell))
		return (ERROR);
	remove_quotes(shell);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	return (SUCCESS);
}
