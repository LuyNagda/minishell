/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:23:40 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/17 17:26:57 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include "string_utils.h"

static int	check_arg(t_commands *command)
{
	int	i;

	i = 0;
	while (command->arguments[1][i])
	{
		if (!ft_strchr("-n", command->arguments[1][i]))
			return (0);
		i++;
	}
	return (1);
}

int	exec_echo(t_minishell *shell, t_commands *command)
{
	size_t		index;

	if (!command->arguments[1])
		return (ft_printf("\n"), 0);
	if (ft_str_equals(command->arguments[1], "$?"))
		return (ft_printf("%d\n", g_status_code), 0);
	if (check_arg(command) == 1)
		index = 2;
	else
		index = 1;
	while (command->arguments[index])
	{
		ft_printf("%s", command->arguments[index++]);
		if (command->arguments[index])
				ft_printf(" ");
	}
	if (check_arg(command) == 0)
		ft_printf("\n");
	return (0);
}
