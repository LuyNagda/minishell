/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:28:58 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 10:10:32 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_quote_is_closed(const char *line)
{
	size_t	index;
	int		open;

	index = 0;
	open = 0;
	while (line[index])
	{
		if (open == 0)
		{
			if (line[index] == '\"')
				open = 1;
			else if (line[index] == '\'')
				open = 2;
		}
		else if (open == 1 && line[index] == '\"')
			open = 0;
		else if (open == 2 && line[index] == '\'')
			open = 0;
		index++;
	}
	if (open == 0)
		return 1;
	else
		return 0;
}

int	ft_index_is_in_quotes(const char *line, size_t pos)
{
	size_t	index;
	int		open;

	index = 0;
	open = 0;
	while (line[index] && pos != index)
	{
		if (open == 0)
		{
			if (line[index] == '\"')
				open = 1;
			else if (line[index] == '\'')
				open = 2;
		}
		else if (open == 1 && line[index] == '\"')
			open = 0;
		else if (open == 2 && line[index] == '\'')
			open = 0;
		index++;
	}
	if (open == 0)
		return 0;
	else
		return 1;
}