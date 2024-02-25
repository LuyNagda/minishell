/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/24 16:08:24 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <unistd.h>

void	error_msg(t_minishell *shell, t_pipex *pipex, char *string)
{
	perror(string);
	free_and_exit(shell, pipex, EXIT_FAILURE);
}

void	command_dir_error(t_commands *command)
{
	if (!ft_str_contains(command->arguments[0], "/", 0))
	{
		ft_putstr_fd(command->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (access(command->arguments[0], F_OK) == 0)
	{
		ft_putstr_fd(command->arguments[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd(command->arguments[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	free_and_exit(t_minishell *shell, t_pipex *pipex, int code)
{
	t_env_map	*node;
	int			status_code;

	node = env_map_find_node(shell->env_map, "?");
	if (code != -1)
		status_code = code;
	else
		status_code = ft_atoi(node->value);
	close(pipex->c_pipe[0]);
	close(pipex->c_pipe[1]);
	ft_flush_command_list(shell->commands);
	ft_flush_tokens(shell->parsing_cmd.tokens);
	if (shell && shell->env_map)
		env_map_flush(shell->env_map);
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->status_string)
		free(pipex->status_string);
	if (pipex->envp)
		ft_free_split(pipex->envp);
	if (shell && shell->sended_line)
		free(shell->sended_line);
	exit(status_code);
}

void	close_fds_pipex(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	close(pipex->c_pipe[1]);
	if (pipex->o_pipe[0] != -1
		&& (command->position == shell->command_amount - 1))
		close(pipex->o_pipe[0]);
	else if (pipex->o_pipe[0] != -1)
		close(pipex->o_pipe[0]);
	if (!(command->position == shell->command_amount - 1))
		pipex->o_pipe[0] = pipex->c_pipe[0];
	if (shell->doc_fd > 0)
		close(shell->doc_fd);
}
