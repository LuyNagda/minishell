/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:30:23 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/22 14:53:34 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/string_utils.h"
#include <stdlib.h>

char	*ft_strdup(const char *source)
{
	void	*v;
	size_t	index;

	if (!source)
		return (NULL);
	v = malloc(ft_strlen(source) + 1 * sizeof (char));
	if (!v)
		return (v);
	index = 0;
	while (source[index])
	{
		((char *)v)[index] = source[index];
		index++;
	}
	((char *)v)[index] = '\0';
	return (v);
}
