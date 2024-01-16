/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:57 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/16 14:17:17 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "string_utils.h"
#include "ft_printf.h"

static char	*get_cwd_for_cd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strdup(cwd));
	else
		return (NULL);
}

int	exec_cd(t_minishell *shell, t_commands *command)
{
	t_env_map	*node;
	t_env_map	*oldpwd;
	t_env_map	*pwd;

	node = env_map_find_node(shell->env_map, "HOME");
	if (command->arguments_amount > 2)
		return (ft_printf("cd: too many arguments\n"), 1);
	else if (node != NULL && command->arguments_amount == 1 && chdir(node->value) != 0)
		return (ft_printf("cd: %s: %s\n", strerror(errno), command->arguments[0]), 127);
	else if (command->arguments[1])
	{
		if (chdir(command->arguments[1]) != 0)
			return (ft_printf("cd: %s: %s\n", strerror(errno), command->arguments[0]), 1);
	}
	oldpwd = env_map_find_node(shell->env_map, "PWD");
	if (oldpwd)
		env_map_replace(shell->env_map, "OLDPWD", oldpwd->value);
	env_map_replace(shell->env_map, "PWD", get_cwd_for_cd());
}

