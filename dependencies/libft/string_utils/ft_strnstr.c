/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:29:02 by jbadaire          #+#    #+#             */
/*   Updated: 2023/10/02 23:21:24 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	text_index;
	size_t	word_index;

	text_index = 0;
	word_index = 0;
	if (needle[0] == 0 || haystack == needle)
		return ((char *) haystack);
	while (haystack[text_index] && text_index < len)
	{
		if (haystack[text_index] && haystack[text_index] == needle[word_index])
		{
			while (haystack[text_index + word_index] == needle[word_index])
			{
				if (++word_index + text_index > len)
					return (NULL);
				if (needle[word_index] == '\0')
					return ((char *) &haystack[text_index]);
			}
			word_index = 0;
		}
		text_index++;
	}
	return (NULL);
}
