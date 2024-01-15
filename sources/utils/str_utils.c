/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:54:43 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/15 11:47:35 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "char_utils.h"
#include "string_utils.h"
#include "memory_utils.h"

/**
 * @brief Compares two strings for equality.
 *
 * This function compares the two strings `str1` and `str2` character by
 * character. It returns 1 if the strings are equal and 0 otherwise. If either
 * `str1` or `str2` is NULL, it returns 0.
 *
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return 1 if the strings are equal, 0 otherwise.
 */
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

/**
 * @brief Checks if a substring is present in a source string.
 *
 * This function checks if the specified substring `search` is present in the
 * source string `src` starting from the specified index `starting_search`.
 *
 * @param src The source string to check.
 * @param search The substring to look for in the source string.
 * @param starting_search The index in the source string to start the search from.
 * @return 1 if the substring is found, 0 otherwise.
 */
int	ft_str_contains(const char *src, const char *search, size_t starting_search)
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
			return (1);
		src_index++;
	}
	return (0);
}

/**
 * @brief Finds the index of the first occurrence of a substring in a source string.
 *
 * This function searches for the first occurrence of the specified substring
 * `search` in the source string `src`, starting from the specified index
 * `starting_search`. If found, it updates the `start_at` pointer with the index
 * where the substring starts.
 *
 * @param src The source string to search.
 * @param search The substring to find in the source string.
 * @param start_at A pointer to store the index where the substring starts.
 * @param starting_search The index in the source string to start the search from.
 * @return 1 if the substring is found, 0 otherwise.
 */
int	ft_str_index_of(const char *src, const char *search, size_t *start_at, size_t starting_search)
{
	size_t	src_index;
	size_t	search_index;

	src_index = starting_search;
	while (ft_strlen(src) > src_index)
	{
		search_index = 0;
		while (search[search_index] && src[search_index + src_index] == search[search_index])
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

char *build_str_from_array(char **array)
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
	return string;
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

/**
 * @brief Checks if a string starts with a given value.
 *
 * This function checks whether the string `src` starts with the substring `value`.
 * It returns 1 if `src` starts with `value`, 0 otherwise. If either `src` or
 * `value` is NULL, it returns 0.
 *
 * @param src The string to check.
 * @param value The substring to check for at the beginning of `src`.
 * @return 1 if `src` starts with `value`, 0 otherwise.
 */
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

/**
 * @brief Copies a portion of a string 2D array starting from a given index.
 *
 * This function copies a portion of the string 2D array `src` starting on the
 * specified index `start`. It returns a new dynamically allocated string 2D array.
 * The copying continues until the end of the original 2D array. The returned 2D array
 * is terminated with a NULL pointer.
 *
 * @param src The source string array to copy from.
 * @param start The index from which to start copying.
 * @return A new string array containing the copied elements, or NULL on failure.
 *         The returned array is terminated with a NULL pointer.
 */
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
			break;
		dest[index] = current;
		start++;
		index++;
	}
	return (dest);
}

char **ft_increase_string_array(char **src)
{
	size_t array_len;
	char	**array;

	if (!src)
		return (ft_calloc(2, sizeof (char  *)));
	array_len = ft_str_tab_len(src);
	array = ft_calloc(array_len + 2, sizeof (char *));
	return (array);
}