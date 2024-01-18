/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:06 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/18 20:17:19 by luynagda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_minishell *shell, t_commands *command)
{
	shell->env_map = env_map_remove_from_key(shell->env_map, command->arguments[1]);
	if (shell->env_map == NULL)
		env_map_replace_or_add(shell->env_map, "?", "1");
	else
		env_map_replace_or_add(shell->env_map, "?", "0");
}
