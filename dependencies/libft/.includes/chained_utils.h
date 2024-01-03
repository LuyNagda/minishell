/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_libft.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 03:35:05 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/03 03:43:00 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAINED_UTILS_H
# define CHAINED_UTILS_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list			*ft_lst_new(void *content);
t_list			*ft_lst_last(t_list *lst);
void			ft_lst_add_front(t_list **lst, t_list *new);
void			ft_lst_add_back(t_list **lst, t_list *new);
void			ft_lst_delone(t_list *lst, void (*del)(void *), void (*free_func)(void *ptr));
void			ft_lst_clear(t_list **lst, void (*del)(void *), void (*free_func)(void *ptr));
void			ft_lst_iter(t_list *lst, void (*f)(void *));
int				ft_lst_size(t_list *lst);

#endif
