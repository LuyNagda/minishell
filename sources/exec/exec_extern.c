/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:19:33 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/06 14:28:23 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>

void	exec_simple_cmd(t_minishell *shell, char *command)
{
	int		index;
	int		sub_process_pid;
	char	**envp;
	char	**path_array;
	char	*path;
	char	**split;
	char	cwd[1024];

	index = 0;
	envp = env_map_to_array(shell->env_map);
	path_array = convert_path_to_array(shell->env_map);
	split = ft_split(command, ' ');
	if (!split)
		exit(1);
	if (ft_str_equals(split[0], "pwd"))
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		else
			ft_printf("%s\n", cwd);
		return ;
	}
	if (ft_str_equals(split[0], "env"))
	{
		while (envp[index])
			ft_printf("%s\n", envp[index++]);
		return ;
	}
	if (ft_str_equals(split[0], "cd"))
	{
		if (split[2])
		{
			ft_printf("cd: too many arguments\n");
			return ;
		}
		if (split[1])
		{
			if (chdir(split[1]) != 0)
				ft_printf("cd: %s: %s\n", strerror(errno), split[1]);
		}
		else if (chdir("/home/lunagda") != 0)
			ft_printf("cd: %s: %s\n", strerror(errno), split[1]);
		return ;
	}
	if (ft_str_equals(split[0], "clear"))
	{
		ft_printf("\ec");
		return ;
	}
	if (ft_str_equals(split[0], "exit"))
	{
		shell->is_running = _false;
		return ;
	}
	path = find_command(split[0], path_array);
	if (path == NULL)
		return ;
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
