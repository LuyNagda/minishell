/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:22:26 by jbadaire          #+#    #+#             */
/*   Updated: 2023/10/14 15:22:26 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/put_utils.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	index;

	if (!s)
		return (0);
	index = 0;
	while (s[index] && s[index] != '\0')
	{
		ft_putchar_fd(s[index], fd);
		index++;
	}
	return (index);
}
