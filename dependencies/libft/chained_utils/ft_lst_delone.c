/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 05:25:42 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 05:25:47 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/chained_utils.h"

void	ft_lst_delone(t_list *lst, void (*del)(void *), \
void (*free_func)(void *ptr))
{
	del(lst->content);
	free_func(lst);
}
