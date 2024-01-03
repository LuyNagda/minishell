/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 03:43:28 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 03:48:48 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_UTILS_H
# define CHAR_UTILS_H

int	ft_is_sign(int character);
int	ft_is_space(int character);
int	ft_is_whitespace(int character);
int	ft_is_alpha_num(int character);
int	ft_is_alpha(int character);
int	ft_is_ascii(int character);
int	ft_is_digit(int character);
int	ft_is_print(int character);

int	ft_to_lower(int character);
int	ft_to_upper(int character);

#endif
