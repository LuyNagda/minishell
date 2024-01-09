/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:38 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 20:25:38 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/ft_printf.h"

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