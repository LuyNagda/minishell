/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimmy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:20:20 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:24:04 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "chained_utils.h"
# include "char_utils.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "memory_utils.h"
# include "put_utils.h"
# include "string_utils.h"


int				ft_atoi(const char *nptr);
long			ft_atoi_long(const char *nptr);
char			*ft_itoa(int n);

#endif
