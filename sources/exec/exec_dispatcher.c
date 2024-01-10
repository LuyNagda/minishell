/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:38:24 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 02:03:44 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(t_commands *command)
{
	return
	(ft_str_starts_with(command->command_name, "clear")
	 || ft_str_starts_with(command->command_name, "cd")
	 || ft_str_starts_with(command->command_name, "pwd")
	 || ft_str_starts_with(command->command_name, "exit")
	 || ft_str_starts_with(command->command_name, "echo")
	 || ft_str_starts_with(command->command_name, "export")
	 || ft_str_starts_with(command->command_name, "unset")
	 || ft_str_starts_with(command->command_name, "env"));
}

void ft_dispatch_command(t_minishell *shell)
{
	t_commands	*tmp;
	if (!shell || !shell->commands)
		return ;
	tmp = shell->commands;
	while (tmp)
	{
		if (tmp->error_during_creation)
			break;
		ft_display_commands_list(shell->commands);
		if (!is_builtins(tmp))
			exec_cmd(shell, tmp);
		else
			ft_dispatch_builtin(shell, tmp);
		tmp = tmp->next_node;
	}
}

int	ft_dispatch_builtin(t_minishell *shell, t_commands *command)
{
	if (ft_str_equals(command->command_name, "clear"))
		g_status_code = exec_clear();
	else if (ft_str_equals(command->command_name, "echo"))
			exec_echo(shell, command);
	else if (ft_str_equals(command->command_name, "cd"))
		g_status_code = exec_cd(shell, command);
	else if (ft_str_equals(command->command_name, "pwd"))
		g_status_code = exec_pwd(shell);
	else if (ft_str_equals(command->command_name, "export"))
			exec_export(shell, command);
	else if (ft_str_equals(command->command_name, "unset"))
		g_status_code = exec_unset(shell, command);
	else if (ft_str_equals(command->command_name, "env"))
		g_status_code = exec_env(shell);
	else if (ft_str_equals(command->command_name, "exit"))
		g_status_code = exec_exit(shell);
	return (g_status_code);
}
