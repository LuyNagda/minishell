/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:19:33 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/04 21:53:12 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	exec_simple_cmd(t_minishell *minishell, char *command)
{
	int		index;
	int		sub_process_pid;
	char	**envp;
	char	**path_array;

	char	*folder_path;
	char	*binary_path;
	char	**split;

	index = 0;
	envp = env_map_to_array(minishell->env_map);
	path_array = convert_path_to_array(minishell->env_map);
	split = ft_split(minishell->sended_line, ' ');
	if (!split)
		exit(1);
	sub_process_pid = fork();
	if (sub_process_pid == -1)
		return ;
	if (sub_process_pid == 0)
	{
		while (path_array[index])
		{
			folder_path = ft_strjoin(path_array[index], "/");
			if (!folder_path)
				exit(1);
			binary_path = ft_strjoin(folder_path, split[0]);
			if (!binary_path)
				exit(1);
			execve(binary_path, split, envp);
			free(folder_path);
			free(binary_path);
			index++;
		}
		exit(127) ;
	}
	waitpid(sub_process_pid, NULL, 0);
	ft_free_split(envp);
	ft_free_split(path_array);
	ft_free_split(split);
}

