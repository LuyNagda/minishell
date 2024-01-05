/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:22:40 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/05 14:45:57 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

void	child_one(t_pipex *pipex)
{
	if (dup2(pipex->c_pipe[0], STDIN_FILENO) == -1)
		perror("DUP2 failed");
	if (dup2(pipex->c_pipe[1], STDOUT_FILENO) == -1)
		perror("DUP2 failed");
	if (pipex->path == NULL)
		exit(EXIT_FAILURE);
	if (execve(pipex->path, pipex->command, 0) == -1)
		ft_printf("%s: %s", strerror(errno), pipex->command[0]);
	exit(EXIT_FAILURE);
}

void	child_middle(t_pipex *pipex)
{
	if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
		perror("DUP2 failed");
	if (dup2(pipex->c_pipe[1], STDOUT_FILENO) == -1)
		perror("DUP2 failed");
	if (pipex->path == NULL)
		exit(EXIT_FAILURE);
	if (execve(pipex->path, pipex->command, 0) == -1)
		ft_printf("%s: %s", strerror(errno), pipex->command[0]);
	exit(EXIT_FAILURE);
}

void	child_last(t_pipex *pipex)
{
	if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
		perror("DUP2 failed");
	if (pipex->path == NULL)
		exit(EXIT_FAILURE);
	if (execve(pipex->path, pipex->command, 0) == -1)
		ft_printf("%s: %s", strerror(errno), pipex->command[0]);
	exit(EXIT_FAILURE);
}

void	exec_simple_pipex_loop(t_pipex *pipex)
{
	while (pipex->split[pipex->index])
	{
		pipex->temp = ft_strtrim(pipex->split[pipex->index], " ");
		pipex->command = ft_split(pipex->temp, ' ');
		free(pipex->temp);
		if (pipe(pipex->c_pipe) == -1)
			perror("Can't create pipe");
		pipex->path = find_command(pipex->command[0], pipex->path_array);
		pipex->sub_process_pid = fork();
		if (pipex->sub_process_pid < 0)
			perror("Fork");
		if (pipex->index == 0 && pipex->sub_process_pid == 0)
			child_one(pipex);
		else if (pipex->index && (pipex->index < pipex->num_of_commands - 1) && pipex->sub_process_pid == 0)
			child_middle(pipex);
		else if (pipex->index == pipex->num_of_commands - 1 && pipex->sub_process_pid == 0)
			child_last(pipex);
		close(pipex->c_pipe[1]);
		pipex->o_pipe[0] = pipex->c_pipe[0];
		wait(NULL);
		pipex->index++;
		ft_free_split(pipex->command);
		free(pipex->path);
	}
}

void	exec_simple_pipex(t_minishell *shell, char *line)
{
	t_pipex	pipex;

	pipex.index = 0;
	pipex.num_of_commands = 0;
	pipex.envp = env_map_to_array(shell->env_map);
	pipex.path_array = convert_path_to_array(shell->env_map);
	pipex.split = ft_split(line, '|');
	if (!pipex.split)
		exit(1);
	while (pipex.split[pipex.num_of_commands])
		pipex.num_of_commands++;
	exec_simple_pipex_loop(&pipex);
	ft_free_split(pipex.envp);
	ft_free_split(pipex.path_array);
	ft_free_split(pipex.split);
}
