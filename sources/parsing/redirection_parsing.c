/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/18 00:28:38 by luynagda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "string_utils.h"
#include <stdio.h>

static int	count_redirection(t_commands *command, char *character)
{
	int		i;
	int		count;
	char	**tmp;

	i = 0;
	count = 0;
	tmp = command->arguments;
	while (tmp[i])
	{
		if (!ft_strncmp(tmp[i], character, 1))
			count++;
		i++;
	}
	return (count);
}

static void	remove_file_from_command(t_commands *command)
{
	int		i;
	int		j;
	char	**tmp;
	char	**result;

	i = 0;
	tmp = command->arguments;
	while (tmp[i] && ft_strncmp(tmp[i], ">", 1))
		i++;
	j = i;
	while (tmp[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i - 2));
	command->arguments_amount = i - 1;
	i = 0;
	while (i < j)
	{
		result[i] = ft_strdup(tmp[i]);
		i++;
	}
	while (tmp[j + 2])
	{
		result[i] = ft_strdup(tmp[j + 2]);
		i++;
		j++;
	}
	result[i] = 0;
	ft_free_split(command->arguments);
	command->arguments = result;
}

void	out_redirection_parsing(t_commands *command)
{
	int			redirection;
	int			i;
	int			count;
	t_commands	*tmp;

	tmp = command;
	count = count_redirection(tmp, ">");
	while (count)
	{
		i = 0;
		redirection = has_redirection(tmp, '>');
		if (redirection)
		{
			while (tmp->arguments[i] && ft_strncmp(tmp->arguments[i], ">", 1))
				i++;
			if (redirection == 1)
				tmp->output_fd = open(tmp->arguments[++i], O_CREAT | O_RDWR | O_TRUNC, 0777);
			else if (redirection == 2)
				tmp->output_fd = open(tmp->arguments[++i], O_WRONLY | O_APPEND | O_CREAT, 0777);
			remove_file_from_command(tmp);
		}
		if (count > 1)
			close(command->output_fd);
		count--;
	}
}
