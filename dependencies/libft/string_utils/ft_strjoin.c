/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:30:19 by jbadaire          #+#    #+#             */
/*   Updated: 2022/11/24 14:30:19 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../.includes/string_utils.h"

static int	ft_fill(void **mlc, char const *text, int mlc_index)
{
	int	index;

	index = 0;
	while (text[index])
	{
		((char *)mlc)[mlc_index] = text[index];
		index++;
		mlc_index++;
	}
	return (mlc_index);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	void	*mlc;
	int		size;

	if (!s1 || !s2)
		return (NULL);
	mlc = malloc(sizeof(char ) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!mlc)
		return (NULL);
	size = ft_fill(mlc, s1, 0);
	size = ft_fill(mlc, s2, size);
	((char *) mlc)[size] = '\0';
	return ((char *) mlc);
}
