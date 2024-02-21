/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:00:38 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/21 14:17:05 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/string_utils.h"
#include "../.includes/memory_utils.h"
#include <stdlib.h>

/**
 * @brief	Allocates and returns a new string that is a copy of the string 's1',
 *			excluding characters specified in 'set' at the beginning 
 *			and end of the string.
 *
 * @param	s1	Original string.
 * @param	set	String representing the set of characters to 
 * 				be removed from the beginning and end of 's1'.
 *
 * @return	A pointer to the new string, or NULL in case of 
 * 			memory allocation failure.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s_start;
	size_t	s_end;
	char	*mlc;

	if (!s1)
		return (NULL);
	s_start = 0;
	s_end = (int)ft_strlen(s1);
	while (s_start < s_end && ft_strchr(set, s1[s_start]) != NULL)
		s_start++;
	while (s_end > s_start && ft_strchr(set, s1[s_end - 1]) != NULL)
		s_end--;
	mlc = malloc(sizeof(char) * s_end - s_start + 1);
	if (!mlc)
		return (NULL);
	ft_memcpy(mlc, s1 + s_start, s_end - s_start);
	mlc[s_end - s_start] = '\0';
	return (mlc);
}
