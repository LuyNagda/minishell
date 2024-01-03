/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:31:02 by jbadaire          #+#    #+#             */
/*   Updated: 2022/11/24 14:31:55 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	index;

	index = 1;
	while (index <= n)
	{
		((char *) s)[index -1] = (char) c;
		index++;
	}
	return (s);
}
