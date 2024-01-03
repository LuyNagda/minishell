/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:39:32 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 03:53:22 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/ft_printf.h"

int	ft_args_handler(char character, va_list params)
{
	int	value;

	value = 0;
	if (character == 'c')
		value = ft_get_char(params);
	else if (character == 's')
		value = ft_get_string(params);
	else if (character == 'u')
		value = ft_get_unsigned_integer(params);
	else if (character == 'd' || character == 'i')
		value = ft_get_integer(params);
	else if (character == 'x')
		value = ft_get_base16(params, "0123456789abcdef");
	else if (character == 'X')
		value = ft_get_base16(params, "0123456789ABCDEF");
	else if (character == 'p')
		value = ft_get_address(params, "0123456789abcdef");
	else if (character == '%')
		value = ft_putchar_fd('%', 1);
	return (value);
}
