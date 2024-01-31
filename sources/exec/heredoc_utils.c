/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:56 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/31 14:03:53 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "put_utils.h"
#include "string_utils.h"
#include "get_next_line.h"

static void	here_doc_error_handling(t_minishell *shell,
			t_commands *command, t_pipex *pipex)
{
	close(command->input_fd);
	command->input_fd = open(".here_doc", O_RDONLY);
	if (command->input_fd < 0)
	{
		perror("here_doc");
		free_and_exit(shell, pipex, 126);
	}
	if (dup2(command->input_fd, STDIN_FILENO) == -1)
		error_msg("DUP2 failed");
	close(command->input_fd);
}

void	here_doc(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	int		i;
	char	*line;

	i = 0;
	if (has_heredoc(command, "<<") && command->arguments_amount != 1)
	{
		heredoc_parsing(shell, command, "<<", pipex);
		while (command->here_doc[i])
		{
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			while (ft_strncmp(command->here_doc[i],
					line, ft_strlen(command->here_doc[i])))
			{
				ft_putstr_fd(line, command->input_fd);
				free(line);
				ft_putstr_fd("> ", 1);
				line = get_next_line(0);
			}
			free(line);
			i++;
		}
		ft_free_split(command->here_doc);
		here_doc_error_handling(shell, command, pipex);
	}
}

void	normal_redirections(t_minishell *shell,
		t_commands *command, t_pipex *pipex)
{
	if (has_redirection(command, '<'))
	{
		redirection_parsing(shell, command, "<", pipex);
		if (command->input_fd > 0)
		{
			if (dup2(command->input_fd, STDIN_FILENO) == -1)
				error_msg("DUP2 failed");
			close(command->input_fd);
		}
		else
		{
			perror("bash");
			free_and_exit(shell, pipex, errno);
		}
	}
}
