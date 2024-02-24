/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:23:35 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/24 11:41:54 by jbadaire         ###   ########.fr       */
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

static char	*get_delimiter(t_minishell *shell, char *str)
{
	t_env_map	*env_map;

	if (!str)
		return (NULL);
	env_map = env_map_get_from_value(shell->env_map, str);
	if (!env_map)
		return (ft_strdup(str));
	return (ft_strjoin("$", env_map->key));
}

int	here_doc_execution(t_minishell *shell, t_commands *tmp, int i)
{
	char	*line;
	char	*delimiter;

	delimiter = get_delimiter(shell, tmp->arguments[i]);
	ft_putstr_fd("heredoc> ", 0);
	line = get_next_line(0);
	if (g_signal_state == SIGINT)
		return (free(delimiter), free(line), 1);
	if (check_for_eof(tmp->arguments[i], line))
		return (free(delimiter), 0);
	while (ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		line = expand_line(line, shell->env_map, !tmp->args_quoted[i]);
		ft_putstr_fd(line, shell->doc_fd);
		free(line);
		ft_putstr_fd("heredoc> ", 0);
		line = get_next_line(0);
		if (g_signal_state == SIGINT)
			return (free(delimiter), free(line), 1);
		if (check_for_eof(tmp->arguments[i], line))
			return (free(delimiter), 0);
	}
	return (free(delimiter), free(line), 0);
}
