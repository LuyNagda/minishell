/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:23:35 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/21 13:25:38 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "put_utils.h"
#include "string_utils.h"
#include "get_next_line.h"
#include <signal.h>
#include <stdio.h>

static int	check_for_eof(char *here_doc, char *line)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document ", 2);
		ft_putstr_fd("at line 1 delimited by end-of-file", 2);
		ft_putstr_fd(" (wanted `", 2);
		ft_putstr_fd(here_doc, 2);
		ft_putendl_fd("')", 2);
		return (1);
	}
	return (0);
}

int	here_doc_execution(t_minishell *shell, t_commands *tmp, int i)
{
	char	*line;

	ft_putstr_fd("heredoc> ", 0);
	line = get_next_line(0);
	if (g_signal_state == SIGINT)
		return (free(line), 1);
	if (check_for_eof(tmp->arguments[i], line))
		return (0);
	line = expand_line(line, shell->env_map, !tmp->args_quoted[i]);
	while (ft_strncmp(tmp->arguments[i],
			line, ft_strlen(tmp->arguments[i])))
	{
		ft_putstr_fd(line, tmp->input_fd);
		free(line);
		ft_putstr_fd("heredoc> ", 0);
		line = get_next_line(0);
		if (g_signal_state == SIGINT)
			return (free(line), 1);
		if (check_for_eof(tmp->arguments[i], line))
			return (0);
		line = expand_line(line, shell->env_map, !tmp->args_quoted[i]);
	}
	free(line);
}
