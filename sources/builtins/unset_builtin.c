/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:06 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/21 14:45:32 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include "char_utils.h"

t_parsing_result	parse_argument(char *arg)
{
	size_t	index;

	if (!arg)
		return (ERROR);
	if (!ft_is_alpha(arg[0]) && arg[0] != '_')
		return (INVALID_INPUT);
	index = 1;
	while (arg[index])
	{
		if (!ft_is_alpha_num(arg[index]) && arg[index] != '_')
			return (INVALID_INPUT);
		index++;
	}
	return (SUCCESS);
}

void	exec_unset(t_minishell *shell, t_commands *command)
{
	size_t	index;

	index = 1;
	while (command->arguments[index])
	{
		if (parse_argument(command->arguments[index]) != SUCCESS)
		{
			printf("unset: `%s': not a valid identifier\n",
				command->arguments[index++]);
			continue ;
		}
		shell->env_map = env_map_remove_from_key(shell->env_map,
				command->arguments[index]);
		if (shell->env_map == NULL)
			env_map_replace_or_add(shell->env_map, "?", "1");
		else
			env_map_replace_or_add(shell->env_map, "?", "0");
		index++;
	}
}
