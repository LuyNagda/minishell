/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/23 15:17:43 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "string_utils.h"

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
