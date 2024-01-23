/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:54:43 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/23 15:01:24 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "char_utils.h"
#include "string_utils.h"
#include "memory_utils.h"

char	ft_get_last_char_iw(char *line)
{
	size_t	index;

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
	size_t	index;

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

int	ft_str_starts_with(const char *src, const char *value)
{
	int	i;

	if (!src || !value)
		return (0);
	i = 0;
	while (src[i] && value[i] && src[i] == value[i])
		i++;
	if (value[i] == '\0')
		return (1);
	return (0);
}

char	**ft_memcpy_array(char **src, char **dest, size_t start)
{
	char	*current;
	size_t	index;
	size_t	tab_len;

	if (!src || !dest)
		return (NULL);
	tab_len = ft_str_tab_len(src);
	if (tab_len <= 0)
		return (NULL);
	index = 0;
	while (src[start] && tab_len >= start)
	{
		current = ft_strdup(src[start]);
		if (!current)
			break ;
		dest[index] = current;
		start++;
		index++;
	}
	return (dest);
}

char	**ft_increase_string_array(char **src)
{
	size_t	array_len;
	char	**array;

	if (!src)
		return (ft_calloc(2, sizeof(char *)));
	array_len = ft_str_tab_len(src);
	array = ft_calloc(array_len + 2, sizeof (char *));
	return (array);
}
