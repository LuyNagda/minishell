/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:06 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 21:41:33 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	exec_unset(t_minishell *shell, t_commands *command)
{
	shell->env_map = env_map_remove_from_key(shell->env_map, command->arguments[0]);
	return (0);
}