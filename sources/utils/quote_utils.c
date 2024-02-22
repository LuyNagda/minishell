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

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static void	update_quote_status(int *inside_squotes, \
	int *inside_dquotes, char c)
{
	if (c == '\'')
		*inside_squotes = !(*inside_squotes);
	else if (c == '"')
		*inside_dquotes = !(*inside_dquotes);
}

int	variable_in_quotes(const char *str, size_t index)
{
	int		ins_s_quotes;
	int		ins_d_quotes;
	size_t	i;

	ins_s_quotes = 0;
	ins_d_quotes = 0;
	i = 0;
	while (i <= index)
	{
		if (i == 0)
			update_quote_status(&ins_s_quotes, &ins_d_quotes, str[i]);
		else if (is_quote(str[i]))
			update_quote_status(&ins_s_quotes, &ins_d_quotes, str[i]);
		i++;
	}
	if (ins_s_quotes)
		return (0);
	if (ins_d_quotes || !ins_s_quotes)
		return (1);
	return (0);
}
