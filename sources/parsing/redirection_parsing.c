/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/17 15:20:23 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "minishell.h"
#include "string_utils.h"
#include "ft_printf.h"

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
	while (tmp[j])
		j++;
	result = (char **)malloc(sizeof(char *) * (j - i + 1));
	command->arguments_amount = j - i;
	j = 0;
	while (j < i)
		result[j++] = ft_strdup(tmp[j]);
	result[j] = 0;
	ft_free_split(command->arguments);
	command->arguments = result;
}

void	out_redirection_parsing(t_commands *commands)
{
	int			redirection;
	int			i;
	t_commands *tmp;

	tmp = commands;
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
}
