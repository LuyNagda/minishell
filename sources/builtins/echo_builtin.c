/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:23:40 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/15 12:30:39 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "minishell.h"

void	exec_echo(t_minishell *shell, t_commands *commands)
{
	t_env_map	*tmp;
	size_t		index;

	index = 1;
	while (commands->arguments[index])
	{
		ft_printf("%s\n", commands->arguments[index++]);
	}
	commands->has_already_executed = _true;
}
