/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:28:58 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/21 14:51:58 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_is_closed(const char *line)
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
		return (1);
	else
		return (0);
}

int	ft_index_is_in_quotes(const char *line, size_t pos)
{
	size_t	index;
	int		open;

	index = 0;
	open = 0;
	if (!line)
		return (0);
	while (line[index])
	{
		if (open == 0 && index != pos)
		{
			if (line[index] == '\"')
				open = 1;
			else if (line[index] == '\'')
				open = 2;
		}
		else if ((open == 1 && line[index] == '\"')
			|| (open == 2 && line[index] == '\''))
			open = 0;
		if (index == pos)
			break ;
		index++;
	}
	return (open != 0);
}
