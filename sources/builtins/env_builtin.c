/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:38 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/24 08:46:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "put_utils.h"
#include <fcntl.h>
#include <unistd.h>

static void	print_error(char *arg, char *msg)
{
	ft_putstr_fd("env: ‘", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("’: ", 2);
	ft_putendl_fd(msg, 2);
}

void	exec_env(t_minishell *shell, t_commands *command)
{
	t_env_map	*head;

	if (command->arguments[1])
	{
		if (ft_str_contains(command->arguments[1], "/", 0)
			&& access(command->arguments[1], F_OK) == 0)
		{
			print_error(command->arguments[1], "Permission Denied");
			env_map_replace_or_add(shell->env_map, "?", "126");
		}
		else
		{
			print_error(command->arguments[1], "No such file or directory");
			env_map_replace_or_add(shell->env_map, "?", "127");
		}
		return ;
	}
	head = shell->env_map;
	while (head)
	{
		if (head->has_equal && !ft_str_equals(head->key, "?"))
			printf("%s=%s\n", head->key, head->value);
		head = head->next_node;
	}
	env_map_replace_or_add(shell->env_map, "?", "0");
}
