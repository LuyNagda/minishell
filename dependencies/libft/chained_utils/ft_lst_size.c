/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:19:37 by jbadaire          #+#    #+#             */
/*   Updated: 2023/01/17 17:20:14 by jbadaire         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/chained_utils.h"

int	ft_lst_size(t_list *lst)
{
	int	index;

	index = 0;
	while (lst)
	{
		lst = lst->next;
		index++;
	}
	return (index);
}
