/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:22:40 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/05 14:09:15 by lunagda          ###   ########.fr       */
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

void	child_one(char **command, int pipe[2], char *path)
{
	if (dup2(pipe[0], STDIN_FILENO) == -1)
		perror("DUP2 failed");
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
		perror("DUP2 failed");
	if (path == NULL)
		exit(EXIT_FAILURE);
	if (execve(path, command, 0) == -1)
		ft_printf("%s: %s", strerror(errno), command[0]);
	exit(EXIT_FAILURE);
}

void	child_middle(char **command, int c_pipe[2], int o_pipe[2], char *path)
{
	if (dup2(o_pipe[0], STDIN_FILENO) == -1)
		perror("DUP2 failed");
	if (dup2(c_pipe[1], STDOUT_FILENO) == -1)
		perror("DUP2 failed");
	if (path == NULL)
		exit(EXIT_FAILURE);
	ft_printf("This is from middle child: \n");
	if (execve(path, command, 0) == -1)
		ft_printf("%s: %s", strerror(errno), command[0]);
	exit(EXIT_FAILURE);
}

void	child_last(char **command, int o_pipe[2], char *path)
{
	if (dup2(o_pipe[0], STDIN_FILENO) == -1)
		perror("DUP2 failed");
	if (path == NULL)
		exit(EXIT_FAILURE);
	if (execve(path, command, 0) == -1)
		ft_printf("%s: %s", strerror(errno), command[0]);
	exit(EXIT_FAILURE);
}

void	exec_simple_pipex(t_minishell *shell, char *line)
{
	int		index;
	int		sub_process_pid;
	int		c_pipe[2];
	int		o_pipe[2];
	int		num_of_commands;
	char	**envp;
	char	**path_array;
	char	*path;
	char	**split;
	char	**command;

	index = 0;
	num_of_commands = 0;
	envp = env_map_to_array(shell->env_map);
	path_array = convert_path_to_array(shell->env_map);
	split = ft_split(line, '|');
	if (!split)
		exit(1);
	while (split[num_of_commands])
		num_of_commands++;
	while (split[index])
	{
		split[index] = ft_strtrim(split[index], " ");
		command = ft_split(split[index], ' ');
		if (pipe(c_pipe) == -1)
			perror("Can't create pipe");
		path = find_command(command[0], path_array);
		sub_process_pid = fork();
		if (sub_process_pid < 0)
			perror("Fork");
		if (index == 0 && sub_process_pid == 0)
			child_one(command, c_pipe, path);
		else if (index && (index < num_of_commands - 1) && sub_process_pid == 0)
			child_middle(command, c_pipe, o_pipe, path);
		else if (index == num_of_commands - 1 && sub_process_pid == 0)
			child_last(command, o_pipe, path);
		close(c_pipe[1]);
		o_pipe[0] = c_pipe[0];
		wait(NULL);
		index++;
	}
}
