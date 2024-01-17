/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:22:40 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/18 00:53:44 by luynagda         ###   ########.fr       */
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

static void	redirections(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (command->position > 0)
	{
		if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
			error_msg("DUP2 failed");
	}
	if (has_redirection(command, '>'))
	{
		out_redirection_parsing(command);
		if (dup2(command->output_fd, STDOUT_FILENO) == -1)
			error_msg("DUP2 failed");
		close(command->output_fd);
	}
	else if (shell->command_amount != 1 && command->position < shell->command_amount - 1)
	{
		if (dup2(pipex->c_pipe[1], STDOUT_FILENO) == -1)
			error_msg("DUP2 failed");
	}
}

static void	exec_command(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (command->position != 0)
		close(pipex->o_pipe[0]);
	close(pipex->c_pipe[0]);
	close(pipex->c_pipe[1]);
	if (command->is_builtin)
	{
		ft_dispatch_builtin(shell, command);
		exit(127);
	}
	if (execve(command->path, command->arguments, pipex->envp) == -1)
	{
		if (command->path == NULL)
			ft_printf("command not found: %s\n", command->arguments[0]);
		else
			ft_printf("%s: %s\n", strerror(errno), command->arguments[0]);
	}
	exit(EXIT_FAILURE);
}

void	child(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	redirections(shell, command, pipex);
	exec_command(shell, command, pipex);
}

void	exec_cmd_loop(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (pipe(pipex->c_pipe) == -1)
		error_msg("Pipe");
	pipex->pid[command->position] = fork();
	if (pipex->pid[command->position] < 0)
		error_msg("Fork");
	if (pipex->pid[command->position] == 0)
		child(shell, command, pipex);
	close(pipex->c_pipe[1]);
	if (pipex->o_pipe[0] != -1 || (command->position == shell->command_amount - 1))
		close(pipex->o_pipe[0]);
	if (!(command->position == shell->command_amount - 1))
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
	close(pipex.o_pipe[0]);
	close(pipex.c_pipe[0]);
	close(pipex.c_pipe[1]);
	pipex.index = 0;
	while (pipex.index < shell->command_amount)
		waitpid(pipex.pid[pipex.index++], &pipex.status, 0);
	pipex.status_string = ft_itoa(WEXITSTATUS(pipex.status));
	env_map_replace(shell->env_map, "?", pipex.status_string);
	free(pipex.status_string);
	ft_free_split(pipex.envp);
}
