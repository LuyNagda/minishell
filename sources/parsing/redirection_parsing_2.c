/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/24 15:23:46 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "string_utils.h"
#include <stdio.h>

int	count_redirection(t_commands *command, char *character)
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

void	remove_file_from_command(t_commands *command,
	char *character, int i)
{
	int		j;
	char	**tmp;
	char	**result;

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
		result[i] = ft_strdup(tmp[i + 2]);
		i++;
		j++;
	}
	result[j] = 0;
	ft_free_split(command->arguments);
	command->arguments = result;
}

int	has_multiple_redirection(t_commands *command, char *character)
{
	if (!ft_strncmp(">", character, 1))
		return (has_redirection(command, '>'));
	else
		return (has_redirection(command, '<'));
}

void	add_back_command_path(t_minishell *shell, t_commands *command)
{
	if (command->arguments_amount > 0)
	{
		if (command->path)
			free(command->path);
		command->path = find_command(shell->env_map, command->arguments[0]);
	}
}

void	close_fds(t_minishell *shell, t_pipex *pipex, t_commands *tmp)
{
	if (tmp->input_fd < 0)
		perror(tmp->infile);
	if (tmp->outfile < 0)
		perror(tmp->outfile);
	free_and_exit(shell, pipex, 126);
}
