/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:19:33 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/04 16:01:08 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void	exec_simple_cmd(t_minishell *shell, char *command)
{
	int		index;
	int		sub_process_pid;
	char	**envp;
	char	**path_array;
	char	*path;
	char	*binary_path;
	char	**split;

	if (ft_str_equals(command, "clear"))
	{
		ft_printf("\ec");
		return ;
	}
	if (ft_str_equals(command, "exit"))
	{
		free(command);
		shell->is_running = _false;
		return ;
	}
	index = 0;
	envp = env_map_to_array(shell->env_map);
	path_array = convert_path_to_array(shell->env_map);
	path = find_command(command, path_array);
	if (path == NULL)
		return ;
	split = ft_split(command, ' ');
	if (!split)
		exit(1);
	sub_process_pid = fork();
	if (sub_process_pid == -1)
		return ;
	if (sub_process_pid == 0)
	{
		if (execve(path, split, 0) == -1)
			ft_printf("%s: %s", strerror(errno), split[0]);
		exit(127);
	}
	wait(NULL);
	ft_free_split(envp);
	ft_free_split(path_array);
	ft_free_split(split);
}

