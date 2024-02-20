/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:45 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/19 14:30:21 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	get_pwd(t_minishell *shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (1);
	else
		return (0);
}

void	exec_pwd(t_minishell *shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		env_map_replace_or_add(shell->env_map, "?", "0");
	}
	else
	{
		printf("Error occurred during executing pwd.\n");
		env_map_replace_or_add(shell->env_map, "?", "1");
	}
}
