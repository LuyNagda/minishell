/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/26 14:38:28 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "string_utils.h"
#include <errno.h>
#include <string.h>

static void	out_redirection(t_commands *tmp, int redirection, int i)
{
	if (redirection == 1)
		tmp->output_fd = open(tmp->arguments[++i],
				O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
		tmp->output_fd = open(tmp->arguments[++i],
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	tmp->outfile = tmp->arguments[i];
}

static void	in_redirection(t_commands *tmp, int redirection, int i)
{
	if (redirection == 1)
	{
		tmp->input_fd = open(tmp->arguments[++i], O_RDONLY);
		tmp->infile = tmp->arguments[i];
	}
}

static void	main_parsing(t_minishell *shell, t_commands *tmp,
			t_pipex *pipex, char *character)
{
	int	i;
	int	redirection;

	i = 0;
	redirection = has_multiple_redirection(tmp, character);
	if (redirection)
	{
		while (tmp->arguments[i]
			&& ft_strncmp(tmp->arguments[i], character, 1))
			i++;
		if (!ft_strncmp(">", character, 1))
			out_redirection(tmp, redirection, i);
		else
			in_redirection(tmp, redirection, i);
		if (tmp->input_fd < 0 || tmp->outfile < 0)
		{
			if (tmp->input_fd < 0)
				perror(tmp->infile);
			if (tmp->outfile < 0)
				perror(tmp->outfile);
			free_and_exit(shell, pipex);
		}
		remove_file_from_command(tmp, character, i);
	}
}

void	redirection_parsing(t_minishell *shell,
	t_commands *command, char *character, t_pipex *pipex)
{
	int			count;
	t_commands	*tmp;

	tmp = command;
	count = count_redirection(tmp, character);
	while (count)
	{
		main_parsing(shell, tmp, pipex, character);
		if (count > 1)
		{
			if (tmp->output_fd)
				close(tmp->output_fd);
			if (tmp->input_fd)
				close(tmp->input_fd);
		}
		count--;
	}
	add_back_command_path(shell, command);
}
