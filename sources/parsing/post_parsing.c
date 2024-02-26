/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:42:42 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/26 18:00:26 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "string_utils.h"
#include "put_utils.h"

static t_boolean	is_special_token(t_tokens *token)
{
	return (token->type == REDIRECT_IN || \
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
			if (is_special_token(tmp2) || tmp2->type == PIPE)
				return (_false);
		}
		tmp = tmp->next;
	}
	return (_true);
}

static void	add_path_to_commands(t_minishell *shell)
{
	t_commands	*command;
	
	command = shell->commands;
	while (command)
	{
		if (is_builtins(command))
			command->path = ft_strdup("builtin");
		else
			command->path = find_command(shell->env_map, command->arguments[0]);
		command = command->next_node;
	}
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
		return (ft_putstr_fd(shell->messages.other_input_error, 2),
			ft_free_token(end_token), INVALID_INPUT);
	ft_add_back_token(&shell->parsing_cmd.tokens, end_token);
	if (!build_command_loop(shell, NULL, 0))
		return (ft_delete_token(&shell->parsing_cmd.tokens, end_token), ERROR);
	remove_quotes(shell);
	add_path_to_commands(shell);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	ft_delete_token(&shell->parsing_cmd.tokens, end_token);
	return (SUCCESS);
}
