/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:14:43 by jbadaire          #+#    #+#             */
/*   Updated: 2023/01/17 17:14:59 by jbadaire         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include ".includes/libft.h"

static int	ft_count_size(long int number)
{
	int	index;

	if (number == 0)
		return (1);
	index = 0;
	while (number)
	{
		number = number / 10;
		index++;
	}
	return (index);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		is_transformed;
	int		mlc_size;
	char	*mlc;

	nb = n;
	is_transformed = 0;
	if (n < 0)
	{
		nb = (long) n * -1;
		is_transformed = 1;
	}
	mlc_size = ft_count_size(nb) + is_transformed;
	mlc = ft_calloc(mlc_size + 1, sizeof(char));
	if (!mlc)
		return (0);
	while (mlc_size)
	{
		mlc[--mlc_size] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		mlc[mlc_size] = '-';
	return (mlc);
}
