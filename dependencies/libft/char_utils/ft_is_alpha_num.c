/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 03:52:10 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 03:52:11 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/char_utils.h"

int	ft_is_alpha_num(int character)
{
	return (ft_is_alpha(character) || ft_is_digit(character));
}
