/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_upper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 03:51:26 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 03:51:29 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_to_upper(int character)
{
	if (character >= 'a' && character <= 'z')
		return (character - 32);
	return (character);
}
