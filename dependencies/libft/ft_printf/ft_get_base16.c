/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:10:35 by jbadaire          #+#    #+#             */
/*   Updated: 2023/09/12 14:58:19 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/ft_printf.h"

int	ft_get_base16(va_list param, char *base)
{
	unsigned int	number;

	number = va_arg(param, unsigned int);
	return (ft_putnbr_base(number, 16, base, 0));
}
