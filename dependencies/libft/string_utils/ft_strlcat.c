/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:30:14 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:09:23 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/string_utils.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	dst_size;

	index = 0;
	dst_size = ft_strlen(dst);
	if (size < dst_size)
		return (ft_strlen(src) + size);
	if (size <= 0)
		return (ft_strlen(src));
	while (src[index] && dst_size < size - 1)
	{
		dst[dst_size] = src[index];
		dst_size++;
		index++;
	}
	dst[dst_size] = '\0';
	return (dst_size + ft_strlen(&src[index]));
}
