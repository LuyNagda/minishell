/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:13:33 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/23 15:03:34 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int	has_heredoc(t_commands *command, char *here_doc)
{
	size_t	index;

	index = 0;
	while (command->arguments[index])
	{
		if (ft_str_equals(command->arguments[index], here_doc))
			return (1);
		index++;
	}
	return (0);
}

static void	remove_heredoc_from_command(t_commands *command,
			char *here_doc, int i)
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
		result[j] = ft_strdup(tmp[i + 2]);
		i++;
		j++;
	}
	result[j] = 0;
	ft_free_split(command->arguments);
	command->arguments = result;
}

void	heredoc_parsing(t_minishell *shell, t_commands *command, char *here_doc)
{
	int			redirection;
	int			i;
	t_commands	*tmp;

	tmp = command;
	i = 0;
	redirection = has_heredoc(tmp, "<<");
	if (redirection)
	{
		while (tmp->arguments[i] && !ft_str_equals(tmp->arguments[i], here_doc))
			i++;
		tmp->input_fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
		tmp->here_doc = ft_strdup(tmp->arguments[++i]);
		remove_heredoc_from_command(tmp, here_doc, i - 1);
	}
	if (command->path)
		free(command->path);
	command->path = find_command(shell->env_map, command->arguments[0]);
}
