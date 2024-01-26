/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/26 13:38:41 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "put_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>

void	error_msg(char *string)
{
	perror(string);
	exit(EXIT_FAILURE);
}

void	free_and_exit(t_minishell *shell, t_pipex *pipex)
{
	ft_flush_command_list(shell->commands);
	ft_flush_tokens(shell->parsing_cmd.tokens);
	env_map_flush(shell->env_map);
	ft_free_split(pipex->envp);
	free(pipex->pid);
	free(shell->sended_line);
	exit(EXIT_FAILURE);
}

void	here_doc(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	char	*line;

	if (has_heredoc(command, "<<") && command->arguments_amount != 1)
	{
		heredoc_parsing(shell, command, "<<", pipex);
		line = readline("$>");
		while (!ft_str_equals(command->here_doc, line))
		{
			ft_putstr_fd(line, command->input_fd);
			ft_putstr_fd("\n", command->input_fd);
			free(line);
			line = readline("$>");
		}
		free(line);
		close(command->input_fd);
		command->input_fd = open(".here_doc", O_RDONLY);
		if (command->input_fd < 0)
		{
			perror("here_doc");
			free_and_exit(shell, pipex);
		}
		if (dup2(command->input_fd, STDIN_FILENO) == -1)
			error_msg("DUP2 failed");
		close(command->input_fd);
	}
}

void	normal_redirections(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (has_redirection(command, '<'))
	{
		redirection_parsing(shell, command, "<");
		if (command->input_fd > 0)
		{
			if (dup2(command->input_fd, STDIN_FILENO) == -1)
				error_msg("DUP2 failed");
			close(command->input_fd);
		}
		else
		{
			perror("bash");
			free_and_exit(shell, pipex);
		}
	}
}
