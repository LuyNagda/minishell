/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:13:33 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/23 20:45:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	has_heredoc(t_commands *command, char *here_doc)
{
	size_t	index;

	index = 0;
	while (command->arguments[index])
	{
		if (ft_str_equals(command->arguments[index], here_doc)
			&& !command->args_quoted[index])
			return (1);
		index++;
	}
	return (0);
}

static size_t	count_here_doc(t_commands *command, char *here_doc)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	while (command->arguments[index])
	{
		if (ft_str_equals(command->arguments[index], here_doc))
			count++;
		index++;
	}
	return (count);
}

static void	remove_heredoc_from_command(t_commands *command,
			char *here_doc, int i)
{
	size_t		j;
	char		**tmp;
	char		**result;

	tmp = command->arguments;
	j = ft_str_tab_len(tmp);
	result = (char **)malloc(sizeof(char *) * (j - 1));
	command->arguments_amount = j - 2;
	j = 0;
	while (j < i)
	{
		result[j] = ft_strdup(tmp[j]);
		j++;
	}
	while (tmp[i + 2])
	{
		result[j] = ft_strdup(tmp[i + 2]);
		i++;
		j++;
	}
	result[j] = 0;
	ft_free_split(command->arguments);
	command->arguments = result;
}

static void	heredoc_loop(t_minishell *shell,
		t_commands *tmp, char *here_doc, t_pipex *pipex)
{
	int			i;
	int			j;
	size_t		count;
	char		*line;

	j = 0;
	count = count_here_doc(tmp, "<<");
	while (count)
	{
		i = 0;
		while (tmp->arguments[i] && !ft_str_equals(tmp->arguments[i], here_doc))
			i++;
		tmp->input_fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (tmp->input_fd < 0)
		{
			perror("here_doc");
			free_and_exit(shell, pipex, 126);
		}
		if (here_doc_execution(shell, tmp, i + 1))
			free_and_exit(shell, pipex, 0);
		remove_heredoc_from_command(tmp, here_doc, i);
		if (count != 1)
			close(tmp->input_fd);
		count--;
	}
}

void	heredoc_parsing(t_minishell *shell,
		t_commands *command, char *here_doc, t_pipex *pipex)
{
	int			redirection;
	t_commands	*tmp;

	tmp = command;
	redirection = has_heredoc(tmp, "<<");
	if (redirection)
		heredoc_loop(shell, tmp, here_doc, pipex);
	add_back_command_path(shell, command);
}
