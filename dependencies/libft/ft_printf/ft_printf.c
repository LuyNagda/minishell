/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:43:52 by jbadaire          #+#    #+#             */
/*   Updated: 2023/09/12 14:57:14 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	params;
	int		index;
	int		return_value;
	int		tmp_value;

	index = 0;
	return_value = 0;
	va_start(params, str);
	while (str[index])
	{
		if (str[index] == '%')
			tmp_value = ft_args_handler(str[++index], params);
		else
			tmp_value = ft_putchar_fd(str[index], 1);
		if (tmp_value == -1)
		{
			va_end(params);
			return (0);
		}
		return_value += tmp_value;
		index++;
	}
	va_end(params);
	return (return_value);
}
