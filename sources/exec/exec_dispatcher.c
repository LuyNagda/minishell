/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:38:24 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/15 12:07:43 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(t_commands *command)
{
	return
	(ft_str_starts_with(command->arguments[0], "clear")
	 || ft_str_starts_with(command->arguments[0], "cd")
	 || ft_str_starts_with(command->arguments[0], "pwd")
	 || ft_str_starts_with(command->arguments[0], "exit")
	 || ft_str_starts_with(command->arguments[0], "echo")
	 || ft_str_starts_with(command->arguments[0], "export")
	 || ft_str_starts_with(command->arguments[0], "unset")
	 || ft_str_starts_with(command->arguments[0], "env"));
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
		if (!is_builtins(tmp))
			exec_cmd(shell, tmp);
		else
			ft_dispatch_builtin(shell, tmp);
		tmp = tmp->next_node;
	}
}

int	ft_dispatch_builtin(t_minishell *shell, t_commands *command)
{
	if (ft_str_equals(command->arguments[0], "clear"))
		g_status_code = exec_clear();
	else if (ft_str_equals(command->arguments[0], "echo"))
			exec_echo(shell, command);
	else if (ft_str_equals(command->arguments[0], "cd"))
		g_status_code = exec_cd(shell, command);
	else if (ft_str_equals(command->arguments[0], "pwd"))
		g_status_code = exec_pwd(shell);
	else if (ft_str_equals(command->arguments[0], "export"))
			exec_export(shell, command);
	else if (ft_str_equals(command->arguments[0], "unset"))
		g_status_code = exec_unset(shell, command);
	else if (ft_str_equals(command->arguments[0], "env"))
		g_status_code = exec_env(shell);
	else if (ft_str_equals(command->arguments[0], "exit"))
		g_status_code = exec_exit(shell);
	return (g_status_code);
}
