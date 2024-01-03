/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 04:19:50 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:19:50 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_UTILS_H
# define PUT_UTILS_H

int		ft_putchar_fd(char c, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_put_unsigned_nbr_fd(unsigned int n, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putnbr_base(long long int number, int base_number, char base_array[],\
int value);

void	ft_putendl_fd(char *s, int fd);

#endif
