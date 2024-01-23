/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 23:30:20 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/23 13:32:36 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../.includes/string_utils.h"
#include "../.includes/memory_utils.h"
#include "../.includes/boolean.h"

static size_t	count_delimiter(const char *string, char delimiter)
{
	size_t	index;
	size_t	delimiters;

	index = 0;
	delimiters = 0;
	while (string[index])
	{
		while (string[index] == delimiter)
			index++;
		if (string[index])
		{
			while (string[index] && string[index] != delimiter)
				index++;
			delimiters++;
		}
	}
	return (delimiters);
}

void	ft_free_split(char **words_list)
{
	size_t	index;

	index = 0;
	while (words_list[index])
		free(words_list[index++]);
	free(words_list);
}

static char	**fill_array(const char *string, char delimiter,
		char **words_list, size_t words)
{
	size_t		index;
	size_t		delimiters;
	size_t		sep_i;
	t_boolean	can_read;

	index = 0;
	delimiters = 0;
	while (string[index] && delimiters < words)
	{
		sep_i = 0;
		can_read = index + sep_i < ft_strlen(string);
		if (string[index] != delimiter && can_read)
		{
			while (can_read && string[index + sep_i]
				&& string[index + sep_i] != delimiter)
				can_read = index + sep_i++ < ft_strlen(string);
			words_list[delimiters] = ft_substr(string, index, sep_i);
			if (!words_list[delimiters])
				return (ft_free_split(words_list), NULL);
			index = index + sep_i - 1;
			delimiters++;
		}
		index++;
	}
	return (words_list);
}

char	**ft_split(char const *string, char delimiter)
{
	char	**words_list;
	size_t	count_delimiters;

	if (!string)
		return (NULL);
	count_delimiters = count_delimiter(string, delimiter);
	words_list = ft_calloc(count_delimiters + 1, sizeof(char *));
	if (!words_list)
		return (NULL);
	return (fill_array(string, delimiter, words_list, count_delimiters));
}
