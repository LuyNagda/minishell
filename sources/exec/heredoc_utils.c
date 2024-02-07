/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:56 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/07 12:52:04 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "char_utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "put_utils.h"
#include "string_utils.h"
#include "get_next_line.h"

static void	here_doc_error_handling(t_minishell *shell,
			t_commands *command, t_pipex *pipex)
{
	close(command->input_fd);
	command->input_fd = open(".here_doc", O_RDONLY);
	if (command->input_fd < 0)
	{
		perror("here_doc");
		free_and_exit(shell, pipex, 126);
	}
	if (dup2(command->input_fd, STDIN_FILENO) == -1)
		error_msg("DUP2 failed");
	close(command->input_fd);
}

char	*expand_line(char *line, t_env_map *map, int must_expanded)
{
	size_t	index;
	size_t	key_len;
	char	*before_key;
	char	*key;
	char	*after_key;

	index = 0;
	if (!ft_str_contains(line, "$", 0) || !must_expanded)
		return (line);
	while (line && line[index])
	{
		if (line[index + 1])
		{
			if ((index > 0 && line[index - 1] == '$') && line[index] == '$')
			{
				index++;
				continue;
			}
			if (line[index] == '$' && ft_is_alpha(line[index + 1]) || line[index + 1] == '_' || line[index + 1] == '?')
			{
				key_len = 0;
				while (line[index + key_len] && !ft_is_whitespace(line[index + key_len]))
					key_len++;
				before_key = ft_substr(line, 0, index);
				key = ft_substr(line, index, key_len);
				after_key = ft_substr(&line[index + key_len], 0, ft_strlen(line));
				t_env_map *node = env_map_find_node(map, &key[1]);
				if (node)
				{
					free(key);
					key = ft_strdup(node->value);
				}
				else
				{
					free(key);
					key = ft_strdup("");
				}
				key_len = ft_strlen(key);
				free(line);
				line = ft_strjoin(before_key, key);
				free(before_key);
				free(key);
				key = ft_strjoin(line, after_key);
				free(line);
				line = ft_strdup(key);
				free(key);
				index = index + key_len;
				continue;
			}
		}
		index++;
	}
	return line;
}


void	here_doc(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	int		i;
	char	*line;

	i = 0;
	if (has_heredoc(command, "<<") && command->arguments_amount != 1)
	{
		heredoc_parsing(shell, command, "<<", pipex);
		while (command->here_doc[i])
		{
			ft_putstr_fd("heredoc> ", 1);
			line = get_next_line(0);
			if (!command->expand)
				line = expand_line(line, shell->env_map, 1);
			while (ft_strncmp(command->here_doc[i],
					line, ft_strlen(command->here_doc[i])))
			{
				ft_putstr_fd(line, command->input_fd);
				free(line);
				ft_putstr_fd("heredoc> ", 1);
				line = get_next_line(0);
				line = expand_line(line, shell->env_map, 1);
			}
			free(line);
			i++;
		}
		ft_free_split(command->here_doc);
		here_doc_error_handling(shell, command, pipex);
	}
}

void	normal_redirections(t_minishell *shell,
		t_commands *command, t_pipex *pipex)
{
	if (has_redirection(command, '<'))
	{
		redirection_parsing(shell, command, "<", pipex);
		if (command->input_fd > 0)
		{
			if (dup2(command->input_fd, STDIN_FILENO) == -1)
				error_msg("DUP2 failed");
			close(command->input_fd);
		}
		else
		{
			perror("bash");
			free_and_exit(shell, pipex, errno);
		}
	}
}
