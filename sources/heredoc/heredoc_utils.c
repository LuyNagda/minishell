/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:56 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/23 17:56:02 by lunagda          ###   ########.fr       */
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
		ft_putendl_fd("Please don't delete the .here_doc file.", 2);
		free_and_exit(shell, pipex, 126);
	}
	if (dup2(command->input_fd, STDIN_FILENO) == -1)
		error_msg(shell, pipex, "DUP2 failed");
	close(command->input_fd);
}

static void	expand_key(char **str, t_env_map *map, t_heredoc_line *doc)
{
	t_env_map		*node;

	doc->before_key = ft_substr(*str, 0, doc->index);
	doc->key = ft_substr(*str, doc->index, doc->key_len);
	doc->after_key = ft_substr(&(*str)[doc->index + doc->key_len], \
		0, ft_strlen(*str));
	node = env_map_find_node(map, &doc->key[1]);
	free(doc->key);
	if (node)
		doc->key = ft_strdup(node->value);
	else
		doc->key = ft_strdup("");
	doc->key_len = ft_strlen(doc->key);
	free(*str);
	*str = ft_strjoin(doc->before_key, doc->key);
	free(doc->before_key);
	free(doc->key);
	doc->key = ft_strjoin(*str, doc->after_key);
	free(doc->after_key);
	free(*str);
	*str = ft_strdup(doc->key);
	free(doc->key);
}

char	*expand_line(char *str, t_env_map *map, int must_expanded)
{
	t_heredoc_line	doc;

	doc.index = 0;
	if (!ft_str_contains(str, "$", 0) || !must_expanded)
		return (str);
	while (str && str[doc.index] && str[doc.index + 1])
	{
		if ((doc.index > 0 && str[doc.index - 1] == '$') \
			&& str[doc.index] == '$' && ++doc.index)
			continue ;
		if (str[doc.index] == '$' && ft_is_alpha(str[doc.index + 1]) \
			|| str[doc.index + 1] == '_' || str[doc.index + 1] == '?')
		{
			doc.key_len = 0;
			while (str[doc.index + doc.key_len] && \
				!ft_is_whitespace(str[doc.index + doc.key_len]))
				doc.key_len++;
			expand_key(&str, map, &doc);
			doc.index = doc.index + doc.key_len;
			continue ;
		}
		doc.index++;
	}
	return (str);
}

void	here_doc(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	int		i;
	char	*line;

	i = 0;
	if (has_heredoc(command, "<<") && command->arguments_amount != 1)
	{
		hook_heredoc_signal();
		heredoc_parsing(shell, command, "<<", pipex);
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
				error_msg(shell, pipex, "DUP2 failed");
			close(command->input_fd);
		}
		else
		{
			perror("bash");
			free_and_exit(shell, pipex, errno);
		}
	}
}
