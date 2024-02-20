/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/20 08:20:13 by luynagda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>

void	error_msg(char *string)
{
	perror(string);
	exit(EXIT_FAILURE);
}

void	free_and_exit(t_minishell *shell, t_pipex *pipex, int code)
{
	t_env_map	*node;
	
	ft_flush_command_list(shell->commands);
	ft_flush_tokens(shell->parsing_cmd.tokens);
	if (shell->env_map)
		env_map_flush(shell->env_map);
	if (pipex->envp)
		ft_free_split(pipex->envp);
	if (pipex->pid)
		free(pipex->pid);
	if (shell->sended_line)
		free(shell->sended_line);
	if (code != -1)
		exit(code);
	node = env_map_find_node(shell->env_map, "?");
	exit(node->value);
}
