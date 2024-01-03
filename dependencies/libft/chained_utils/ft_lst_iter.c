/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 05:25:59 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 05:26:01 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/chained_utils.h"

void	ft_lst_iter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
