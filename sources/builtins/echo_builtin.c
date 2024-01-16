/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:23:40 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/16 15:45:04 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "string_utils.h"

static int	check_arg(t_commands *commands)
{
	int	i;

	i = 0;
	while (commands->arguments[1][i])
	{
		if (!ft_strchr("-n", commands->arguments[1][i]))
			return (0);
		i++;
	}
	return (1);
}

void	exec_echo(t_minishell *shell, t_commands *commands)
{
	size_t		index;

	if (check_arg(commands) == 1)
		index = 2;
	else
		index = 1;
	while (commands->arguments[index])
	{
		ft_printf("%s", commands->arguments[index++]);
		if (commands->arguments[index])
				ft_printf(" ");
	}
	if (check_arg(commands) == 0)
		ft_printf("\n");
	commands->has_already_executed = _true;
}
