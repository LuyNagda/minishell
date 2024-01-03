/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:18:30 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:13:20 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../.includes/put_utils.h"

int	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	char			ch;
	int				value;

	value = 0;
	nb = (unsigned int)n;
	if (n < 0)
	{
		nb = nb * -1;
		value += write (fd, "-", 1);
	}
	if (nb <= 9)
	{
		ch = nb + '0';
		value += write(fd, &ch, 1);
	}
	if (nb > 9)
	{
		value += ft_putnbr_fd(nb / 10, fd);
		value += ft_putnbr_fd(nb % 10, fd);
	}
	return (value);
}

int	ft_put_unsigned_nbr_fd(unsigned int n, int fd)
{
	unsigned int	nb;
	char			ch;
	int				value;

	nb = n;
	ch = 0;
	value = 0;
	if (nb <= 9)
	{
		ch = nb + '0';
		value = write(fd, &ch, 1);
	}
	if (nb > 9)
	{
		value = 0;
		value += ft_put_unsigned_nbr_fd(nb / 10, fd);
		value += ft_put_unsigned_nbr_fd(nb % 10, fd);
	}
	return (value);
}

int	ft_putnbr_base(long long int number, int base_number, \
char base_array[], int value)
{
	char	character;

	value = 0;
	if (number >= (long long int)base_number)
	{
		value += ft_putnbr_base(number / base_number, \
		base_number, base_array, value);
		value += ft_putnbr_base(number % base_number, \
		base_number, base_array, value);
	}
	else
	{
		character = base_array[number];
		value += ft_putchar_fd(character, 1);
		return (value);
	}
	return (value);
}
