/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/08 17:58:18 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include <stdlib.h>
#include <stdio.h>

size_t	ft_count_command(t_minishell *shell)
{
	size_t	command_number;

	command_number = 0;
	ft_concat_tokens(shell, _false);
	while (shell->commands.latest_command != NULL)
	{
		if (!ft_quote_is_closed(shell->commands.latest_command))
			ft_concat_quoted_pipes(shell, 0);
		++command_number;
		free(shell->commands.latest_command);
		shell->commands.latest_command = NULL;
		ft_concat_tokens(shell, _false);
	}
	ft_default_cmd_struct(shell, _false);
	return (command_number);
}

void	error_msg(char *string)
{
	perror(string);
	exit(EXIT_FAILURE);
}


char	**trim_command_list(char **command_list)
{
	int		i;
	int		nb;
	char	**result;

	i = 0;
	nb = 0;
	while (command_list[i])
		nb++;
	result = (char **)malloc((nb + 1) * sizeof(char *));
	while (i < nb)
	{
		result[i] = ft_strdup(ft_strtrim(command_list[i], " >"));
		free(command_list[i]);
		i++;
	}
	result[i] = '0';
	return (result);
}
