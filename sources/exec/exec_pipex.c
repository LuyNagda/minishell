/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:22:40 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/16 13:27:21 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

//int	g_status_code;

void	child_one(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (dup2(pipex->c_pipe[0], STDIN_FILENO) == -1)
		error_msg("DUP2 failed");
	if (shell->command_amount != 1)
	{
		if (dup2(pipex->c_pipe[1], STDOUT_FILENO) == -1)
			error_msg("DUP2 failed");
	}
	else if (shell->command_amount == 1 && ft_str_contains(command->raw_command, ">", 0))
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			error_msg("DUP2 failed");
		close(pipex->outfile);
	}
	close(pipex->c_pipe[1]);
	if (command->path == NULL)
		exit(127);
	if (command->is_builtin)
		exit(ft_dispatch_builtin(shell, command));
	if (execve(command->path, command->arguments, pipex->envp) == -1)
		ft_printf("%s: %s", strerror(errno), command->arguments[0]);
	exit(EXIT_FAILURE);
}

void	child_middle(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
		error_msg("DUP2 failed");
	if (dup2(pipex->c_pipe[1], STDOUT_FILENO) == -1)
		error_msg("DUP2 failed");
	close(pipex->o_pipe[0]);
	close(pipex->c_pipe[1]);
	if (command->path == NULL)
		exit(127);
	if (command->is_builtin)
		exit(ft_dispatch_builtin(shell, command));
	if (execve(command->path,command->arguments, pipex->envp) == -1)
		ft_printf("%s: %s", strerror(errno), command->arguments[0]);
	exit(EXIT_FAILURE);
}

void	child_last(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
		error_msg("DUP2 failed");
	if (ft_str_contains(command->raw_command, ">", 0))
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			error_msg("DUP2 failed");
		close(pipex->outfile);
	}
	close(pipex->o_pipe[0]);
    close(pipex->c_pipe[1]);
    close(pipex->c_pipe[0]);
	if (command->path == NULL)
		exit(127);
	if (command->is_builtin)
		exit(ft_dispatch_builtin(shell, command));
	if (execve(command->path, command->arguments, pipex->envp) == -1)
		ft_printf("%s: %s", strerror(errno), command->arguments[0]);
	exit(EXIT_FAILURE);
}

void	exec_cmd_loop(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	//if (has_redirection(command, '>') == 2)
	//{
	//	command->arguments = ft_split(command->raw_command, '>');
	//	command->arguments = trim_command_list(command->arguments);
	//	pipex->outfile = open(command->arguments[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	//	command->arguments = ft_split(command->arguments[0], ' ');
	//}
	//else if (has_redirection(command, '>') == 1)
	//{
	//	command->arguments = ft_split(command->raw_command, '>');
	//	command->arguments = trim_command_list(command->arguments);
	//	pipex->outfile = open(command->arguments[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	//	command->arguments = ft_split(command->arguments[0], ' ');
	//}
	if (pipe(pipex->c_pipe) == -1)
		error_msg("Pipe");
	pipex->pid[command->position] = fork();
	if (pipex->pid[command->position] < 0)
		error_msg("Fork");
	if (command->position == 0 && pipex->pid[command->position] == 0)
	{
		child_one(shell, command, pipex);
	}
	else if ((command->position < shell->command_amount - 1) && pipex->pid[command->position] == 0)
		child_middle(shell, command, pipex);
	else if (command->position && (command->position == shell->command_amount - 1) && pipex->pid[command->position] == 0)
		child_last(shell, command, pipex);
	close(pipex->c_pipe[1]);
	if (pipex->o_pipe[0] != -1)
	{
		close(pipex->o_pipe[0]);
		pipex->o_pipe[0] = -1;
	}
	pipex->o_pipe[0] = pipex->c_pipe[0];
}

void	exec_cmd(t_minishell *shell, t_commands *commands)
{
	t_pipex	pipex;

	pipex.pid = (int *)malloc(sizeof(int) * shell->command_amount);
	pipex.envp = env_map_to_array(shell->env_map);
	if (pipex.envp == NULL)
		return ;
	pipex.o_pipe[0] = -1;
	while (commands)
	{
		exec_cmd_loop(shell, commands, &pipex);
		commands = commands->next_node;
	}
	pipex.index = 0;
	while (pipex.index < shell->command_amount)
	{
		waitpid(pipex.pid[pipex.index], &pipex.status, 0);
		pipex.index++;
	}
	close(pipex.o_pipe[0]);
	g_status_code = WEXITSTATUS(pipex.status);
	ft_free_split(pipex.envp);
}
