/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:30:28 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:08:50 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/string_utils.h"

char	*ft_strchr(const char *s, char character)
{
	size_t	index;

	index = 0;
	if (character == '\0')
		return ((char *) &s[ft_strlen(s)]);
	while ((char)s[index])
	{
		if ((char)s[index] == character)
			return ((char *) s + index);
		index++;
	}
	return (NULL);
}
