/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:05:56 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/24 16:08:32 by lunagda          ###   ########.fr       */
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

void	here_doc_error_handling(t_minishell *shell,
			t_commands *command, t_pipex *pipex)
{
	if (shell->doc_fd != 0)
	{
		close(shell->doc_fd);
		shell->doc_fd = open(".here_doc", O_RDONLY);
		if (shell->doc_fd < 0)
		{
			ft_putendl_fd("Please don't delete the .here_doc file.", 2);
			free_and_exit(shell, pipex, 126);
		}
		if (dup2(shell->doc_fd, STDIN_FILENO) == -1)
			error_msg(shell, pipex, "DUP2 failed");
		close(shell->doc_fd);
	}
}

static void	expand_key(char **str, t_env_map *map, t_heredoc_line *doc)
{
	t_env_map		*node;
	char			*trim;

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
				!ft_is_whitespace(str[doc.index + doc.key_len]) \
				&& !is_quote(str[doc.index + doc.key_len]))
				doc.key_len++;
			expand_key(&str, map, &doc);
			doc.index = doc.index + doc.key_len;
			continue ;
		}
		doc.index++;
	}
	return (str);
}

int	here_doc(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	int		i;
	char	*line;

	i = 0;
	if (has_heredoc(command, "<<") && command->arguments_amount != 1)
	{
		heredoc_parsing(shell, command, "<<", pipex);
		return (1);
	}
	return (0);
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
