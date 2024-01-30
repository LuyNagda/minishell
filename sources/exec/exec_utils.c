/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/30 11:06:35 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <char_utils.h>

#include "minishell.h"
#include "string_utils.h"
#include "put_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <errno.h>

void	error_msg(char *string)
{
	perror(string);
	exit(EXIT_FAILURE);
}

void	free_and_exit(t_minishell *shell, t_pipex *pipex, int code)
{
	ft_flush_command_list(shell->commands);
	ft_flush_tokens(shell->parsing_cmd.tokens);
	env_map_flush(shell->env_map);
	ft_free_split(pipex->envp);
	free(pipex->pid);
	free(shell->sended_line);
	exit(code);
}

size_t	ft_strlen_diff(char *str1, char *str2)
{
	size_t len_1;
	size_t len_2;

	if (!str1 || !str2)
		return 0;
	len_1 = 0;
	len_2 = 0;
	while (str1[len_1])
		len_1++;
	while (str2[len_2])
		len_2++;
	if (len_1 > len_2)
		return (len_1 - len_2);
	if (len_2 > len_1)
		return (len_2 - len_1);
	return (0);
}


char	*expand_line(char *line, t_env_map *map, int must_expanded)
{
	size_t	index;
	size_t	key_len;
	char	*before_key;
	char	*key;
	char	*after_key;

	index = 0;
	if (!ft_str_contains(line, "$", 0))
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
			if (line[index] == '$' && ft_is_alpha(line[index + 1]) || line[index + 1] == '_')
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
	return (line);
}


void	here_doc(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	char	*line;

	if (has_heredoc(command, "<<") && command->arguments_amount != 1)
	{
		heredoc_parsing(shell, command, "<<", pipex);
		line = readline("$>");
		line = expand_line(line, shell->env_map, 1);
		while (!ft_str_equals(command->here_doc, line))
		{
			ft_putstr_fd(line, command->input_fd);
			ft_putstr_fd("\n", command->input_fd);
			line = readline("$>");
			line = expand_line(line, shell->env_map, 1);
		}
		free(line);
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
