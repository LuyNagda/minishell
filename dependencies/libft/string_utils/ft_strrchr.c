/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 04:47:33 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:47:33 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/string_utils.h"

char	*ft_strrchr(const char *s, int c)
{
	int		index;

	index = (int)ft_strlen(s);
	while (index >= 0)
	{
		if ((unsigned char )s[index] == (char)c)
			return ((char *) s + index);
		index--;
	}
	return (NULL);
}
