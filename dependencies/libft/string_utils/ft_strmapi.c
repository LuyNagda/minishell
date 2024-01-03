/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 04:47:18 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:47:18 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../.includes/string_utils.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		index;
	char				*mlc;

	index = 0;
	mlc = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!mlc)
		return (NULL);
	while (s[index])
	{
		mlc[index] = f(index, s[index]);
		index++;
	}
	mlc[index] = '\0';
	return (mlc);
}
