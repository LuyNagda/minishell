/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:08:57 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/04 20:50:40 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/char_utils.h"

static int	is_only_space(char *line)
{
	int	index;
	int	space_amount;

	index = 0;
	space_amount = 0;
	while (line[index])
	{
		if (ft_is_space(line[index]))
			space_amount++;
		index++;
	}
	return (space_amount == index);
}

int	ft_has_valid_history(char *line)
{
	if (is_only_space(line))
		return (0);
	if (line[0] == '\0')
		return (0);
	return (1);
}
