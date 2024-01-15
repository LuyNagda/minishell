/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:15:13 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/15 12:31:50 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_boolean is_builtin(t_minishell *shell)
{
	return (shell->commands->next_node ||\
	ft_str_contains(shell->sended_line, ">", 0) ||\
	ft_str_contains(shell->sended_line, "<", 0));
}

t_parsing_result post_parsing(t_minishell *shell)
{
	if (!build_command_from_tokens(shell))
		return (ERROR);
	shell->is_builtin = is_builtin(shell);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	return (SUCCESS);
}
