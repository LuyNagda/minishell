/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:38 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/17 21:52:10 by luynagda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

void	exec_env(t_minishell *shell)
{
	t_env_map	*head;

	head = shell->env_map;
	while (head)
	{
		if (head->has_equal)
			ft_printf("%s=%s\n", head->key, head->value);
		head = head->next_node;
	}
	env_map_replace_or_add(shell->env_map, "?", "0");
}