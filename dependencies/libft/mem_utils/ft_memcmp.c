/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:44:22 by jbadaire          #+#    #+#             */
/*   Updated: 2023/01/17 17:44:26 by jbadaire         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			index;
	unsigned char	*s1_char;
	unsigned char	*s2_char;

	if (s1 == s2 || n == 0)
		return (0);
	s1_char = ((unsigned char *) s1);
	s2_char = ((unsigned char *) s2);
	index = 0;
	while (index < n)
	{
		if (s1_char[index] == s2_char[index])
			index++;
		else
			return (s1_char[index] - s2_char[index]);
	}
	return (0);
}
