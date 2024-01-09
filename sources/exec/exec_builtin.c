/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:24:01 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/09 15:32:30 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include "../../dependencies/libft/.includes/string_utils.h"

//int	g_status_code;

int	exec_clear(void)
{
	return (ft_printf("\ec"), 0);
}

int	exec_echo(t_minishell *shell, char **split)
{
	t_env_map *tmp;

	if (ft_str_equals(split[1], "$?"))
		return (ft_printf("%d\n", g_status_code), 0);
	else if (ft_str_equals(split[1], "-n"))
	{
		if (!ft_strncmp(split[2], "$", 1))
		{
			tmp = env_map_find_node(shell->env_map, &split[2][1]);
			if (!tmp)
				return (ft_printf("\n"), 0);
			else
				return (ft_printf("%s", tmp->value), 0);			
		}
		else
			return (ft_printf("%s", split[2]), 0);
	}
	else
	{
		if (!ft_strncmp(split[1], "$", 1))
		{
			tmp = env_map_find_node(shell->env_map, &split[1][1]);
			if (!tmp)
				return (ft_printf("\n"), 0);
			else
				return (ft_printf("%s\n", tmp->value), 0);			
		}
		else
			return (ft_printf("%s\n", split[1]), 0);
	}
}

int	exec_cd(t_minishell *shell, char **split)
{
	t_env_map	*node;
	t_env_map	*oldpwd;
	t_env_map	*pwd;
	char		*cwd;

	node = env_map_find_node(shell->env_map, "HOME");
	if (node == NULL)
		return (127);
	if (split[2])
		return (ft_printf("cd: too many arguments\n"), 1);
	else if (split[1])
	{
		if (chdir(split[1]) != 0)
			return (ft_printf("cd: %s: %s\n", strerror(errno), split[1]), 1);
		else
		{
			oldpwd = env_map_find_node(shell->env_map, "PWD");
			env_map_replace(shell->env_map, "OLDPWD", oldpwd->value);
			cwd = get_cwd_for_cd();
			env_map_replace(shell->env_map, "PWD", cwd);
		}
	}
	else if (chdir(node->value) != 0)
		return (ft_printf("cd: %s: %s\n", strerror(errno), split[1]), 127);
	else
	{
		oldpwd = env_map_find_node(shell->env_map, "PWD");
		env_map_replace(shell->env_map, "OLDPWD", oldpwd->value);
		cwd = get_cwd_for_cd();
		env_map_replace(shell->env_map, "PWD", cwd);
	}
}

int	exec_pwd(t_minishell *shell, char **split)
{
	t_env_map	*node;

	node = env_map_find_node(shell->env_map, "PWD");
	if (node == NULL)
		return (ft_printf("PWD has been unset.\n"), 1);
	return (ft_printf("%s\n", node->value), 0);
}

int	exec_builtin(t_minishell *shell, char *line)
{
	char	**split;
	
	split = ft_split(line, ' ');
	if (ft_str_equals(split[0], "clear"))
		g_status_code = exec_clear();
	else if (ft_str_equals(split[0], "echo"))
		g_status_code = exec_echo(shell, split);
	else if (ft_str_equals(split[0], "cd"))
		g_status_code = exec_cd(shell, split);
	else if (ft_str_equals(split[0], "pwd"))
		g_status_code = exec_pwd(shell, split);
	else if (ft_str_equals(split[0], "export"))
		g_status_code = exec_export(shell, split);
	else if (ft_str_equals(split[0], "unset"))
		g_status_code = exec_unset(shell, split);
	else if (ft_str_equals(split[0], "env"))
		g_status_code = exec_env(shell);
	else if (ft_str_equals(split[0], "exit"))
		g_status_code = exec_exit(shell);
	return (ft_free_split(split), g_status_code);
}
