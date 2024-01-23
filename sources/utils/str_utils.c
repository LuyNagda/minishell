/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:54:43 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/23 15:00:23 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "char_utils.h"
#include "string_utils.h"
#include "memory_utils.h"

int	ft_str_equals(const char *str1, const char *str2)
{
	size_t	index;

	if (!str1 || !str2)
		return (0);
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

int	ft_str_contains(const char *src, const char *search, size_t starting_search)
{
	size_t	src_index;
	size_t	search_index;

	src_index = starting_search;
	while (ft_strlen(src) > src_index)
	{
		search_index = 0;
		while (search[search_index]
			&& src[search_index + src_index] == search[search_index])
			search_index++;
		if (search[search_index] == '\0')
			return (1);
		src_index++;
	}
	return (0);
}

int	ft_str_index_of(const char *src, const char *search,
	size_t *start_at, size_t starting_search)
{
	size_t	src_index;
	size_t	search_index;

	src_index = starting_search;
	while (ft_strlen(src) > src_index)
	{
		search_index = 0;
		while (search[search_index]
			&& src[search_index + src_index] == search[search_index])
			search_index++;
		if (search[search_index] == '\0')
		{
			*start_at = src_index;
			return (1);
		}
		src_index++;
	}
	return (0);
}

char	*build_str_from_array(char **array)
{
	size_t	array_index;
	size_t	len;
	size_t	char_index;
	char	*string;

	array_index = 0;
	len = 0;
	while (array[array_index])
		len += ft_strlen(array[array_index++]);
	string = ft_calloc(len + array_index + 1, sizeof(char ));
	if (!string)
		return (NULL);
	array_index = 0;
	len = 0;
	while (array[array_index])
	{
		char_index = 0;
		while (array[array_index][char_index])
			string[len++] = array[array_index][char_index++];
		string[len++] = ' ';
		array_index++;
	}
	return (string);
}

void	ft_replace_whitespace(char *line, char value)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if (ft_is_whitespace(line[index]))
			line[index] = value;
		index++;
	}
}
