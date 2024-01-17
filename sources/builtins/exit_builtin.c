/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:39 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/17 21:52:12 by luynagda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

void	exec_exit(t_minishell *shell)
{
	shell->is_running = _false;
	ft_printf("exit\n");
	env_map_replace_or_add(shell->env_map, "?", "0");
}
