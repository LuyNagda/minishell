/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 04:43:48 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 04:43:51 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/chained_utils.h"

void	ft_lst_clear(t_list **lst, void (*del)(void *), \
void (*free_func)(void *ptr))
{
	t_list	*tmp;

	while (*lst)
	{
		del((*lst)->content);
		tmp = (*lst)->next;
		free_func(*lst);
		*lst = tmp;
	}
}
