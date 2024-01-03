/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:28:58 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/19 13:38:52 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_is_quote(char c, char quote)
{
	return (c == quote);
}

int ft_count_quotes(char *line, char character)
{
	size_t	index;
	int		count;

	index = 0;
	count = 0;
	while (line[index])
	{
		if (ft_is_quote(line[index], character))
			count++;
		index++;
	}
	return (count);
}

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
		return 1;
	else
		return 0;
}

int	ft_index_is_in_quote(const char *line, size_t pos, char quote)
{
	size_t	index;
	int		open;

	index = 0;
	open = 0;
	while (line[index] && pos != index)
	{
		if ((open == 0) && line[index] == quote)
			open = 1;
		else if ((open == 1) && line[index] == quote)
			open = 0;
		index++;
	}
	return (open);
}


int ft_quote_is_closed_range(const char *line, size_t start, size_t end)
{
	int open;

	open = 0;
	while (line[start] && end > start)
	{
		if (open == 0)
		{
			if (line[start] == '\"')
				open = 1;
			else if (line[start] == '\'')
				open = 2;
		}
		else if (open == 1 && line[start] == '\"')
			open = 0;
		else if (open == 2 && line[start] == '\'')
			open = 0;
		start++;
	}
	if (open == 0)
		return 1;
	else
		return 0;
}