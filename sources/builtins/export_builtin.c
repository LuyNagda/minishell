/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:50 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 21:49:52 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../dependencies/libft/.includes/ft_printf.h"
#include "../../includes/minishell.h"

void	exec_export(t_minishell *shell, t_commands *command)
{
	t_env_map 	*node;
	char		**export;

	export = ft_split(command->arguments[0], '=');
	if (!export)
	{
		//TODO: MUST ADDED IN ENVIRONMENT FOR EXPORT COMMAND
		return ;
	}
	//TODO: MUST ADDED IN ENVIRONMENT FOR ENV COMMAND
	//TODO: WARNING export[1] can be null
	//TODO: Please check export test= and export test=test2 and check result in "env" command and "export" command.
	node = env_map_find_node(shell->env_map, export[0]);
	if (node != NULL)
	{
		env_map_replace(shell->env_map, export[0], export[1]);
		ft_free_split(export);
		return;
	}
	node = ft_create_env_node(export[0], export[1], 1, 0);
	env_map_add_back(&shell->env_map, node, 1);
}