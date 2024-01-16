/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:38 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/16 15:12:28 by lunagda          ###   ########.fr       */
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
}