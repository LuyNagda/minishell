/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:42:42 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/15 17:42:46 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_boolean is_builtin(t_minishell *shell)
{
	return (is_builtins(shell->commands) && (!shell->commands->next_node ||\
	ft_str_contains(shell->sended_line, ">", 0) ||\
	ft_str_contains(shell->sended_line, "<", 0)));
}

t_parsing_result post_parsing(t_minishell *shell)
{
	if (!build_command_from_tokens(shell))
		return (ERROR);
	//ft_display_commands_list(shell->commands);
	shell->is_builtin = is_builtin(shell);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	return (SUCCESS);
}
