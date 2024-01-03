/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:30:49 by jbadaire          #+#    #+#             */
/*   Updated: 2022/11/24 14:30:49 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/put_utils.h"

void	ft_putendl_fd(char *string, int file_descriptor)
{
	ft_putstr_fd(string, file_descriptor);
	ft_putchar_fd('\n', file_descriptor);
}
