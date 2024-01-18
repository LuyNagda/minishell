/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:38:24 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/18 13:34:36 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

int has_redirection(t_commands *command, char character)
{
	size_t index;

	index = 0;
	while (command->arguments[index])
	{
		if (command->arguments[index][0] == character && command->arguments[index][1] && command->arguments[index][1] == character)
			return (2);
		else if (command->arguments[index][0] == character)
			return (1);
		index++;
	}
	return (0);
}

void	ft_dispatch_command(t_minishell *shell)
{
	t_commands	*tmp;

	if (has_error(shell))
	{
		env_map_replace(shell->env_map, "?", "1");
		return ;
	}
	tmp = shell->commands;
	//redirection_parsing(tmp, "<");
	//ft_display_commands_list(tmp);
	if (shell->command_amount == 1 && is_builtins(shell->commands) && !(has_redirection(tmp, '>') || has_redirection(tmp, '<')))
		ft_dispatch_builtin(shell, tmp);
	else
		exec_cmd(shell, tmp);
}

void	ft_dispatch_builtin(t_minishell *shell, t_commands *command)
{
	if (ft_str_equals(command->arguments[0], "clear"))
		exec_clear(shell);
	else if (ft_str_equals(command->arguments[0], "echo"))
		exec_echo(shell, command);
	else if (ft_str_equals(command->arguments[0], "cd"))
		exec_cd(shell, command);
	else if (ft_str_equals(command->arguments[0], "pwd"))
		exec_pwd(shell);
	else if (ft_str_equals(command->arguments[0], "export"))
		exec_export(shell, command);
	else if (ft_str_equals(command->arguments[0], "unset"))
		exec_unset(shell, command);
	else if (ft_str_equals(command->arguments[0], "env"))
		exec_env(shell);
	else if (ft_str_equals(command->arguments[0], "exit"))
		exec_exit(shell);
}
