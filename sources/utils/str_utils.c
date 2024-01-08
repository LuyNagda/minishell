/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:54:43 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/08 12:10:47 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/char_utils.h"
#include "../../dependencies/libft/.includes/string_utils.h"

int	ft_str_equals(const char *str1, const char *str2)
{
	size_t	index;

	index = 0;
	while (str1[index] && str2[index])
	{
		if (str1[index] != str2[index])
			return (0);
		index++;
	}
	if (str1[index] != str2[index])
		return (0);
	return (1);
}

int	ft_str_only_whitespace(const char *src)
{
	size_t		index;

	index = 0;
	while (src[index])
	{
		if (!ft_is_whitespace(src[index]))
			return (0);
		index++;
	}
	return (1);
}

int	ft_str_contains(const char *src, const char *search, size_t *start_at, size_t starting_search)
{
	size_t		src_index;
	size_t	search_index;

	src_index = starting_search;
	while (ft_strlen(src) > src_index)
	{
		search_index = 0;
		while (search[search_index] && src[search_index + src_index] == search[search_index])
			search_index++;
		if (search[search_index] == '\0')
		{
			//*start_at = src_index;
			return (1);
		}
		src_index++;
	}
	return (0);	
}

void	ft_replace_whitespace(char *line, char value)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if (ft_is_space(line[index]))
			line[index] = value;
		index++;
	}
}

char	ft_get_last_char_iw(char *line)
{
	size_t index;

	index = ft_strlen(line) -1;
	while (index > 0 && line[index])
	{
		if (ft_is_whitespace(line[index]))
			index--;
		else
			return (line[index]);
	}
	return ('\0');
}

char	ft_get_first_char_iw(char *line)
{
	size_t index;

	index = 0;
	while (line[index])
	{
		if (ft_is_whitespace(line[index]))
			index++;
		else
			return (line[index]);
	}
	return (line[index]);
}