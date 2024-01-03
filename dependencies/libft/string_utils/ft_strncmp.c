/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:29:12 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:09:56 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	t1;
	unsigned char	t2;

	index = 0;
	while ((s1[index] || s2[index]) && index < n)
	{
		t1 = s1[index];
		t2 = s2[index];
		if (t1 < t2 || t1 > t2)
			return (t1 - t2);
		index++;
	}
	return (0);
}
