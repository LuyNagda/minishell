/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:22:40 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/15 16:12:46 by lunagda          ###   ########.fr       */
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
		close(pipex->c_pipe[1]);
	}
	else if (shell->command_amount == 1 && ft_str_contains(command->raw_command, ">", 0))
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			error_msg("DUP2 failed");
		close(pipex->outfile);
	}
	if (pipex->path == NULL)
		exit(127);
	if (ft_str_equals(pipex->path, "builtin"))
		exit(ft_dispatch_builtin(shell, command));
	if (execve(pipex->path, command->arguments, 0) == -1)
		ft_printf("%s: %s", strerror(errno), command->arguments[0]);
	exit(EXIT_FAILURE);
}

void	child_middle(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
		error_msg("DUP2 failed");
	if (dup2(pipex->c_pipe[1], STDOUT_FILENO) == -1)
		error_msg("DUP2 failed");
	close(pipex->c_pipe[1]);
	if (pipex->path == NULL)
		exit(127);
	//if (ft_str_equals(pipex->path, "builtin"))
	//	exit(exec_builtin(shell, pipex->command_list[0]));
	if (execve(pipex->path,command->arguments, 0) == -1)
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
	close(pipex->c_pipe[1]);
	close(pipex->c_pipe[0]);
	close(pipex->o_pipe[0]);
	if (pipex->path == NULL)
		exit(127);
	if (ft_str_equals(pipex->path, "builtin"))
		exit(ft_dispatch_builtin(shell, command));
	if (execve(pipex->path, command->arguments, 0) == -1)
		ft_printf("%s: %s", strerror(errno), command->arguments[0]);
	exit(EXIT_FAILURE);
}

void	exec_cmd_loop(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	//if (ft_str_contains(command->raw_command, ">>", 0))
	//{
	//	pipex->command_list = ft_split(command->raw_command, '>');
	//	pipex->command_list = trim_command_list(pipex->command_list);
	//	pipex->outfile = open(pipex->command_list[1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	//	pipex->command_list = ft_split(pipex->command_list[0], ' ');
	//}
	//else if (ft_str_contains(command->raw_command, ">", 0))
	//{
	//	pipex->command_list = ft_split(command->raw_command, '>');
	//	pipex->command_list = trim_command_list(pipex->command_list);
	//	pipex->outfile = open(pipex->command_list[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	//	pipex->command_list = ft_split(pipex->command_list[0], ' ');
	//}
	//else
	//ft_printf("command posi: %d\n", command->position);
	pipex->command_list = ft_split(command->raw_command, ' ');
	if (pipe(pipex->c_pipe) == -1)
		error_msg("Pipe");
	pipex->path = find_command(command->arguments[0], pipex->path_array);
	pipex->sub_process_pid = fork();
	if (pipex->sub_process_pid < 0)
		error_msg("Fork");
	if (command->position == 0 && pipex->sub_process_pid == 0)
		child_one(shell, command, pipex);
	else if ((command->position < shell->command_amount - 1) && pipex->sub_process_pid == 0)
		child_middle(shell, command, pipex);
	else if (command->position && (command->position == shell->command_amount - 1) && pipex->sub_process_pid == 0)
		child_last(shell, command, pipex);		
	close(pipex->c_pipe[1]);
	if (pipex->o_pipe[0])
		close(pipex->o_pipe[0]);
	pipex->o_pipe[0] = pipex->c_pipe[0];
	ft_free_split(pipex->command_list);
	free(pipex->path);
}

void	exec_cmd(t_minishell *shell, t_commands *commands)
{
	t_pipex	pipex;

	pipex.path_array = convert_path_to_array(shell->env_map);
	if (pipex.path_array == NULL)
		return ;
	while (commands)
	{
		exec_cmd_loop(shell, commands, &pipex);
		commands = commands->next_node;
	}
	close(pipex.o_pipe[0]);
	waitpid(pipex.sub_process_pid, &pipex.status, 0);
	g_status_code = WEXITSTATUS(pipex.status);
	ft_free_split(pipex.path_array);
}
