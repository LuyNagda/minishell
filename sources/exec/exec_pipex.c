/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:22:40 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/24 17:48:35 by lunagda          ###   ########.fr       */
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
	here_doc_error_handling(shell, pipex);
	normal_redirections(shell, command, pipex);
	if (command->arguments_amount == 0)
		free_and_exit(shell, pipex, 0);
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
	if (command->position > 0 && !command->input_fd && !shell->doc_fd)
	{
		if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
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
	if (command->arguments_amount > 0 && (command->path == NULL
			|| (ft_get_last_char_iw(command->path) == '/')))
	{
		command_dir_error(command);
		free_and_exit(shell, pipex, 127);
	}
	execve(command->path, command->arguments, pipex->envp);
	perror(command->arguments[0]);
	free_and_exit(shell, pipex, 1);
}

void	exec_cmd_loop(t_minishell *shell,
			t_commands *command, t_pipex *pipex)
{
	if (here_doc(shell, command)
		&& command->arguments == 0)
	{
		printf("here_doc\n");
		if (shell->command_amount == 1)
			close(shell->doc_fd);
		pipex->close_pipe = 0;
		return ;
	}
	if (pipe(pipex->c_pipe) == -1)
		error_msg(shell, pipex, "Pipe");
	pipex->close_pipe = 1;
	pipex->pid[pipex->index] = fork();
	if (pipex->pid[pipex->index] < 0)
		error_msg(shell, pipex, "Fork");
	if (pipex->pid[pipex->index] == 0)
	{
		redirections(shell, command, pipex);
		exec_command(shell, command, pipex);
	}
	close_fds_pipex(shell, command, pipex);
	pipex->index++;
}

static void	close_wait_free(t_minishell *shell, t_pipex *pipex)
{
	if (pipex->o_pipe[0] != -1)
		close(pipex->o_pipe[0]);
	if (pipex->close_pipe)
	{
		close(pipex->c_pipe[0]);
		close(pipex->c_pipe[1]);
		pipex->i = 0;
		while (pipex->i < pipex->index)
			waitpid(pipex->pid[pipex->i++], &pipex->status, 0);
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
		env_map_replace(shell->env_map, "?", pipex->status_string);
	}
	ft_free_split(pipex->envp);
}

void	exec_cmd(t_minishell *shell, t_commands *commands)
{
	t_pipex		pipex;

	pipex.envp = env_map_to_array(shell->env_map);
	if (pipex.envp == NULL)
		return ;
	pipex.pid = (int *)malloc(sizeof(int) * shell->command_amount);
	if (pipex.pid == NULL)
	{
		ft_free_split(pipex.envp);
		return ;
	}
	shell->doc_fd = 0;
	pipex.status_string = NULL;
	pipex.o_pipe[0] = -1;
	pipex.index = 0;
	while (commands)
	{
		handle_ignored_signal();
		exec_cmd_loop(shell, commands, &pipex);
		commands = commands->next_node;
	}
	close_wait_free(shell, &pipex);
	free(pipex.status_string);
	free(pipex.pid);
	unlink(".here_doc");
}
