/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:39 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/20 17:05:55 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static t_boolean has_only_digits(char *str)
{
	size_t index;

	index = 0;
	while (str[index])
	{
		if (!ft_is_digit(str[index]) && ((str[index] != '-' && index != 0) || (str[index] != '+' && index != 0)))
			return (_false);
		index++;
	}
	return (_true);
}

static char *increment_for_zero(char *str)
{
	size_t index;
	char *copy;

	index = 0;
	copy = str;
	while (str[index] == '0' && str[index + 1] && str[index + 1] == '0') {
		index++;
		copy++;
	}
	return copy;
}

void exec_exit(t_minishell *shell, t_commands *command)
{
	char *first_arg;
	t_env_map *env_map;
	int	exit_code;
	char *result;
	t_boolean must_exit;

	first_arg = NULL;
	must_exit = _true;
	printf("exit\n");
	if (ft_get_arguments_amount(command) > 1)
	{
		first_arg = command->arguments[1];
		if (!has_only_digits(first_arg))
		{
			printf("minishell: exit: %s: numeric argument required\n", first_arg);
			env_map_replace_or_add(shell->env_map, "?", "2");
			exit_code = 2;
		}
		else if (has_only_digits(first_arg) && ft_get_arguments_amount(command) > 2) {
			printf("minishell: exit: too many arguments\n");
			env_map_replace_or_add(shell->env_map, "?", "1");
			must_exit = _false;
		}
		else
			exit_code = ft_atoi(increment_for_zero(first_arg));
	}
	// Only exit
	if (ft_get_arguments_amount(command) == 1)
	{
		env_map = env_map_find_node(shell->env_map, "?");
		if (env_map != NULL)
			exit_code = ft_atoi(env_map->value);
	}
	//exit
	if (must_exit == _false)
		return ;
	result = ft_itoa(exit_code % 256);
	if (result == NULL)
		return;
	env_map_replace_or_add(shell->env_map, "?", result);
	shell->is_running = _false;
	free(result);
}
