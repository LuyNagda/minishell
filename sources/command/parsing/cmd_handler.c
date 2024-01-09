/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:48:23 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/15 12:50:13 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_default_cmd_struct(t_minishell *shell, t_boolean reset_tokens)
{
	shell->parsing_cmd.last_end = 0;
	shell->parsing_cmd.next_start = 0;
	shell->parsing_cmd.latest_command = NULL;
	if (reset_tokens && shell->parsing_cmd.tokens && ft_get_tokens_amount(shell->parsing_cmd.tokens) > 0)
		ft_flush_tokens(shell->parsing_cmd.tokens);
}

