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
#include "string_utils.h"
#include <stdlib.h>

t_parsing_result post_parsing(t_minishell *shell)
{

	if (!build_command_from_tokens(shell))
		return (ERROR);
	shell->command_amount = ft_get_numbers_of_commands(shell->commands);
	//ft_display_commands_list(shell->commands);
	return (SUCCESS);
}
