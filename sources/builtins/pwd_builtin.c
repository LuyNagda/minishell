/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:45 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 20:25:45 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/ft_printf.h"

int	exec_pwd(t_minishell *shell)
{
	t_env_map	*node;

	node = env_map_find_node(shell->env_map, "PWD");
	if (node == NULL)
		return (ft_printf("PWD has been unset.\n"), 1);
	return (ft_printf("%s\n", node->value), 0);
}