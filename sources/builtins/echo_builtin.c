/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:23:40 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/23 17:08:44 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "string_utils.h"

static int	check_arg(t_commands *command)
{
	int	i;
	int	j;

	i = 1;
	while (command->arguments[i])
	{
		j = 1;
		if (command->arguments[i][0] != '-'
			|| !command->arguments[i][1])
			return (i);
		while (command->arguments[i][j])
		{
			if (!ft_strchr("n", command->arguments[i][j]))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	exec_echo(t_minishell *shell, t_commands *command)
{
	size_t		index;

	if (command->arguments_amount == 1)
	{
		printf("\n");
		env_map_replace_or_add(shell->env_map, "?", "0");
		return ;
	}
	if (check_arg(command) > 1)
		index = check_arg(command);
	else
		index = 1;
	while (command->arguments[index])
	{
		printf("%s", command->arguments[index++]);
		if (command->arguments[index])
			printf(" ");
	}
	if (check_arg(command) == 1)
		printf("\n");
	env_map_replace_or_add(shell->env_map, "?", "0");
}
