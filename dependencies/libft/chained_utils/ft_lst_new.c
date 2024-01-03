/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 05:26:13 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 05:26:13 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.includes/chained_utils.h"
#include <stdlib.h>

t_list	*ft_lst_new(void *content)
{
	t_list	*list;

	list = malloc(sizeof (t_list));
	if (!list)
		return (0);
	list->content = content;
	list->next = NULL;
	return (list);
}
