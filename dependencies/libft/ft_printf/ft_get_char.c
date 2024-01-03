/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:47:16 by jbadaire          #+#    #+#             */
/*   Updated: 2023/09/12 13:56:35 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/ft_printf.h"

int	ft_get_char(va_list param)
{
	char	c;

	c = va_arg(param, int);
	return (ft_putchar_fd(c, 1));
}
