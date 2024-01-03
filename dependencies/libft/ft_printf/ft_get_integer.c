/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_integer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:18:42 by jbadaire          #+#    #+#             */
/*   Updated: 2023/09/12 13:57:52 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/ft_printf.h"

int	ft_get_integer(va_list param)
{
	int	value;

	value = va_arg(param, int);
	return (ft_putnbr_fd(value, 1));
}

int	ft_get_unsigned_integer(va_list param)
{
	unsigned int	value;
	int				return_value;

	value = va_arg(param, unsigned int);
	return_value = 0;
	return_value += ft_put_unsigned_nbr_fd(value, 1);
	return (return_value);
}
