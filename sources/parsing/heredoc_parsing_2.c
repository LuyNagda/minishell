/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:23:35 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/19 17:33:32 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "put_utils.h"
#include "string_utils.h"
#include "get_next_line.h"

static int	check_for_eof(char *line)
{
	if (!line)
	{
		ft_putstr_fd("\nminishell: warning: here-document ", 2);
		ft_putendl_fd("at line 1 delimited by end-of-file", 2);
		return (1);
	}
	return (0);
}

void	here_doc_execution(t_minishell *shell, t_commands *tmp, int i)
{
	char	*line;

	tmp->here_doc = ft_strdup(tmp->arguments[++i]);
	tmp->expand = tmp->args_quoted[i];
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	if (check_for_eof(line))
		return ;
	if (!tmp->expand)
		line = expand_line(line, shell->env_map, 1);
	while (ft_strncmp(tmp->here_doc,
			line, ft_strlen(tmp->here_doc)))
	{
		ft_putstr_fd(line, tmp->input_fd);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (check_for_eof(line))
			return ;
		if (!tmp->expand)
			line = expand_line(line, shell->env_map, 1);
	}
	free(line);
}
