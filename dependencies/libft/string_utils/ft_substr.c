/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 04:47:52 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:47:55 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../.includes/string_utils.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*mlc;
	size_t	index;
	size_t	s_size;

	if (!s || s[0] == '\0')
		return (ft_strdup(""));
	s_size = ft_strlen(s);
	if (start >= s_size)
		return (ft_strdup(""));
	if (len > (s_size - start))
		len = s_size - start;
	mlc = malloc(sizeof (char) * (len + 1));
	if (!mlc)
		return (NULL);
	index = 0;
	while (s[index] && index < len)
	{
		mlc[index] = s[start];
		start++;
		index++;
	}
	mlc[index] = '\0';
	return (mlc);
}
