/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:23:40 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 20:27:42 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../dependencies/libft/.includes/ft_printf.h"
#include "../../includes/minishell.h"

void	exec_echo(t_minishell *shell, t_commands *commands)
{
	t_env_map	*tmp;
	size_t		index;

	index = 0;
	while (commands->arguments[index])
	{
		if (ft_str_equals(commands->arguments[0], "-n"))
			index++;
		ft_printf("%s ", commands->arguments[index++]);
	}
	if (!ft_str_equals(commands->arguments[0], "-n"))
		ft_printf("\n");
}
