/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/09 13:52:07 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (shell->env_map)
		env_map_flush(shell->env_map);
	if (pipex->envp)
		ft_free_split(pipex->envp);
	if (pipex->pid)
		free(pipex->pid);
	free(shell->sended_line);
	exit(code);
}
