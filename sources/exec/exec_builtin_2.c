/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:24:01 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/09 12:35:56 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include "../../dependencies/libft/.includes/chained_utils.h"

//int	g_status_code;

int	exec_export(t_minishell *shell, char **split)
{
	t_env_map *head;

	//env_map_add_back(shell->env_map, )
}

int	exec_unset(t_minishell *shell, char **split)
{
	shell->env_map = env_map_remove_from_key(shell->env_map, split[1]);
	if (shell->env_map == NULL)
		return (127);
	else
		return (0);
}

int	exec_env(t_minishell *shell)
{
	t_env_map	*head;

	head = shell->env_map;
	while (head)
	{
		ft_printf("%s=%s\n", head->key, head->value);
		head = head->next_node;
	}
	return (0);
}

int	exec_exit(t_minishell *shell)
{
	shell->is_running = _false;
	return (0);
}
