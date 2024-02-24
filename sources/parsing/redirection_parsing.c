/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/24 15:19:57 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "string_utils.h"
#include "put_utils.h"

static int	out_redirection(t_commands *tmp, int redirection, int i)
{
	if (ft_str_equals(tmp->arguments[i + 1], ">")
		|| ft_str_equals(tmp->arguments[i + 1], ">>")
		|| ft_str_equals(tmp->arguments[i + 1], "<")
		|| ft_str_equals(tmp->arguments[i + 1], "<<"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tmp->arguments[i + 1], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	if (redirection == 1)
		tmp->output_fd = open(tmp->arguments[++i],
				O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
		tmp->output_fd = open(tmp->arguments[++i],
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	tmp->outfile = tmp->arguments[i];
	return (0);
}

static int	in_redirection(t_commands *tmp, int redirection, int i)
{
	if (ft_str_equals(tmp->arguments[i + 1], ">")
		|| ft_str_equals(tmp->arguments[i + 1], ">>")
		|| ft_str_equals(tmp->arguments[i + 1], "<")
		|| ft_str_equals(tmp->arguments[i + 1], "<<"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tmp->arguments[i + 1], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	if (redirection == 1)
	{
		tmp->input_fd = open(tmp->arguments[++i], O_RDONLY);
		tmp->infile = tmp->arguments[i];
	}
	return (0);
}

static void	close_and_free(t_minishell *shell, t_pipex *pipex)
{
	close(pipex->c_pipe[0]);
	close(pipex->c_pipe[1]);
	free_and_exit(shell, pipex, 1);
}

static void	main_parsing(t_minishell *shell, t_commands *tmp,
			t_pipex *pipex, char *character)
{
	int	i;
	int	redirection;

	i = 0;
	redirection = has_multiple_redirection(tmp, character);
	if (redirection)
	{
		while (tmp->arguments[i]
			&& ft_strncmp(tmp->arguments[i], character, 1))
			i++;
		if (!ft_strncmp(">", character, 1)
			&& out_redirection(tmp, redirection, i))
			close_and_free(shell, pipex);
		else if (!ft_strncmp("<", character, 1)
			&& in_redirection(tmp, redirection, i))
			close_and_free(shell, pipex);
		if (tmp->input_fd < 0 || tmp->outfile < 0)
			close_fds(shell, pipex, tmp);
		remove_file_from_command(tmp, character, i);
	}
}

void	redirection_parsing(t_minishell *shell,
	t_commands *command, char *character, t_pipex *pipex)
{
	int			count;
	t_commands	*tmp;

	tmp = command;
	count = count_redirection(tmp, character);
	while (count)
	{
		main_parsing(shell, tmp, pipex, character);
		if (count > 1)
		{
			if (tmp->output_fd)
				close(tmp->output_fd);
			if (tmp->input_fd)
				close(tmp->input_fd);
		}
		count--;
	}
	add_back_command_path(shell, command);
}
