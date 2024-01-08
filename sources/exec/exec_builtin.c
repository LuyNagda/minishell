/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:24:01 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/08 21:33:25 by luynagda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include "../../dependencies/libft/.includes/string_utils.h"

int	g_status_code;

void	exec_clear(void)
{
	ft_printf("\ec");
}

void	exec_echo(t_minishell *shell, char **split)
{
	t_env_map *tmp;

	if (ft_str_equals(split[1], "$?"))
		ft_printf("%d\n", g_status_code);
	else if (ft_str_equals(split[1], "-n"))
	{
		if (!ft_strncmp(split[2], "$", 1))
		{
			tmp = env_map_find_node(shell->env_map, &split[2][1]);
			if (!tmp)
				ft_printf("\n");
			else
				ft_printf("%s", tmp->value);			
		}
		else
			ft_printf("%s", split[2]);
	}
	else
	{
		if (!ft_strncmp(split[1], "$", 1))
		{
			tmp = env_map_find_node(shell->env_map, &split[1][1]);
			if (!tmp)
				ft_printf("\n");
			else
				ft_printf("%s\n", tmp->value);			
		}
		else
			ft_printf("%s\n", split[1]);
	}
}

void	exec_cd(t_minishell *shell, char **split)
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
}

void	exec_pwd(char **split)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		ft_printf("%s\n", cwd);
}

void	exec_builtin(t_minishell *shell, char *line)
{
	char	**split;
	
	split = ft_split(line, ' ');
	if (ft_str_equals(split[0], "clear"))
		exec_clear();
	else if (ft_str_equals(split[0], "echo"))
		exec_echo(shell, split);
	else if (ft_str_equals(split[0], "cd"))
		exec_cd(shell, split);
	else if (ft_str_equals(split[0], "pwd"))
		exec_pwd(split);
	else if (ft_str_equals(split[0], "export"))
		exec_export(shell, split);
	else if (ft_str_equals(split[0], "unset"))
		exec_unset(shell, split);
	else if (ft_str_equals(split[0], "env"))
		exec_env(shell);
	else if (ft_str_equals(split[0], "exit"))
		exec_exit(shell);
	ft_free_split(split);
}
