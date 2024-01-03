/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 03:32:43 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:05:53 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int				ft_printf(const char *str, ...);
int				ft_args_handler(char character, va_list params);
int				ft_get_char(va_list param);
int				ft_get_string(va_list param);
int				ft_get_integer(va_list param);
int				ft_get_unsigned_integer(va_list param);
int				ft_get_address(va_list param, char *base_array);
int				ft_get_base16(va_list param, char *base);

#endif
