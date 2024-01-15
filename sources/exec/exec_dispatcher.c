/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:38:24 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/15 15:49:40 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "ft_printf.h"

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

static t_boolean has_error(t_minishell *shell)
{
	t_commands	*tmp;

	if (!shell || !shell->commands)
		return (_true);
	tmp = shell->commands;
 	while (tmp)
	{
		if (tmp->error_during_creation)
		{
			//TODO: Error during parsing
			return (_true);
		}
		tmp = tmp->next_node;
	}
	return (_false);
}

void ft_dispatch_command(t_minishell *shell)
{
	t_commands	*tmp;

	if (has_error(shell))
		return ;
	tmp = shell->commands;
	if (shell->command_amount == 1)
	{
		if (shell->is_builtin)
			ft_dispatch_builtin(shell, tmp);
		else
			exec_cmd(shell, tmp);
	}
	else
		exec_cmd(shell, tmp);
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
