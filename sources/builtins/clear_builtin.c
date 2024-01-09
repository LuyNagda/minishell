/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:26:37 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 20:26:46 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../dependencies/libft/.includes/ft_printf.h"

int	exec_clear(void)
{
	return (ft_printf("\ec"), 0);
}