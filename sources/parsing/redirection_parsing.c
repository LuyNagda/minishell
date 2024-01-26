/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/26 13:40:04 by lunagda          ###   ########.fr       */
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
}

static void	in_redirection(t_commands *tmp, int redirection, int i)
{
	if (redirection == 1)
	{
		tmp->input_fd = open(tmp->arguments[++i], O_RDONLY);
	}
}

static void	main_parsing(t_commands *tmp, int redirection,
			char *character, int count)
{
	int	i;

	i = 0;
	if (redirection)
	{
		while (tmp->arguments[i]
			&& ft_strncmp(tmp->arguments[i], character, 1))
			i++;
		if (!ft_strncmp(">", character, 1))
			out_redirection(tmp, redirection, i);
		else
			in_redirection(tmp, redirection, i);
		remove_file_from_command(tmp, character, i);
		if (count > 1)
		{
			if (tmp->output_fd)
				close(tmp->output_fd);
			if (tmp->input_fd)
				close(tmp->input_fd);
		}
	}
}

void	redirection_parsing(t_minishell *shell,
	t_commands *command, char *character)
{
	int			redirection;
	int			count;
	t_commands	*tmp;

	tmp = command;
	count = count_redirection(tmp, character);
	while (count)
	{
		redirection = has_multiple_redirection(tmp, character);
		main_parsing(tmp, redirection, character, count);
		count--;
	}
	if (command->arguments_amount > 0)
	{
		if (command->path)
			free(command->path);
		command->path = find_command(shell->env_map, command->arguments[0]);
	}
}
