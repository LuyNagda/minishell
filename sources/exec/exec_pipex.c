/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:22:40 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/23 20:41:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "put_utils.h"
#include "libft.h"

static void	redirections(t_minishell *shell,
			t_commands *command, t_pipex *pipex)
{
	here_doc(shell, command, pipex);
	normal_redirections(shell, command, pipex);
	if (command->arguments_amount == 0)
		free_and_exit(shell, pipex, 0);
	if (command->position > 0 && !command->input_fd && !shell->here_doc_fd)
	{
		if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
			error_msg(shell, pipex, "DUP2 failed");
	}
	if (has_redirection(command, '>'))
	{
		redirection_parsing(shell, command, ">", pipex);
		if (dup2(command->output_fd, STDOUT_FILENO) == -1)
			error_msg(shell, pipex, "DUP2 failed");
		close(command->output_fd);
	}
	else if (shell->command_amount != 1
		&& command->position < shell->command_amount - 1)
	{
		if (dup2(pipex->c_pipe[1], STDOUT_FILENO) == -1)
			error_msg(shell, pipex, "DUP2 failed");
	}
}

static void	exec_command(t_minishell *shell,
			t_commands *command, t_pipex *pipex)
{
	if (command->position != 0 && pipex->o_pipe[0] != -1)
		close(pipex->o_pipe[0]);
	close(pipex->c_pipe[0]);
	close(pipex->c_pipe[1]);
	if (command->is_builtin)
	{
		ft_dispatch_builtin(shell, command);
		free_and_exit(shell, pipex, -1);
	}
	if (command->arguments_amount == 0)
		free_and_exit(shell, pipex, 0);
	if (command->arguments_amount > 0 && command->path == NULL)
	{
		ft_putstr_fd(command->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_and_exit(shell, pipex, 127);
	}
	execve(command->path, command->arguments, pipex->envp);
	perror(command->arguments[0]);
	free_and_exit(shell, pipex, 1);
}

void	exec_cmd_loop(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (pipe(pipex->c_pipe) == -1)
		error_msg(shell, pipex, "Pipe");
	handle_ignored_signal();
	pipex->pid[command->position] = fork();
	if (pipex->pid[command->position] < 0)
		error_msg(shell, pipex, "Fork");
	if (pipex->pid[command->position] == 0)
	{
		redirections(shell, command, pipex);
		exec_command(shell, command, pipex);
	}
	close(pipex->c_pipe[1]);
	if (pipex->o_pipe[0] != -1
		&& (command->position == shell->command_amount - 1))
		close(pipex->o_pipe[0]);
	else if (pipex->o_pipe[0] != -1)
		close(pipex->o_pipe[0]);
	if (!(command->position == shell->command_amount - 1))
		pipex->o_pipe[0] = pipex->c_pipe[0];
}

static void	wait_for_children(t_minishell *shell, t_pipex *pipex)
{
	while (pipex->index < shell->command_amount)
		waitpid(pipex->pid[pipex->index++], &pipex->status, 0);
	if (WIFSIGNALED(pipex->status))
	{
		if (WTERMSIG(pipex->status) == 3)
		{
			ft_putstr_fd("Quit (core dumped)", 2);
			pipex->status_string = ft_strdup("131");
		}
		if (WTERMSIG(pipex->status) == 2)
			pipex->status_string = ft_strdup("130");
		ft_putstr_fd("\n", 2);
	}
	else
		pipex->status_string = ft_itoa(WEXITSTATUS(pipex->status));
}

void	exec_cmd(t_minishell *shell, t_commands *commands)
{
	t_pipex		pipex;
	t_commands	*tmp;

	tmp = commands;
	pipex.pid = (int *)malloc(sizeof(int) * shell->command_amount);
	pipex.envp = env_map_to_array(shell->env_map);
	if (pipex.envp == NULL)
		return ;
	pipex.status_string = NULL;
	pipex.o_pipe[0] = -1;
	while (commands)
	{
		exec_cmd_loop(shell, commands, &pipex);
		commands = commands->next_node;
	}
	if (pipex.o_pipe[0] != -1)
		close(pipex.o_pipe[0]);
	close(pipex.c_pipe[0]);
	close(pipex.c_pipe[1]);
	pipex.index = 0;
	wait_for_children(shell, &pipex);
	env_map_replace(shell->env_map, "?", pipex.status_string);
	ft_free_split(pipex.envp);
	free(pipex.status_string);
	free(pipex.pid);
	unlink(".here_doc");
}
