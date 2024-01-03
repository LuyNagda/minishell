/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:20:40 by jbadaire          #+#    #+#             */
/*   Updated: 2023/01/17 17:42:55 by jbadaire         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*chars;
	size_t			index;

	chars = (unsigned char *) s;
	index = 0;
	while (index < n)
	{
		if (chars[index] == (unsigned char )c)
			return (chars + index);
		index++;
	}
	return (0);
}
