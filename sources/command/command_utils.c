/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:15:54 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/14 15:55:44 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>

int	*ft_fill_args_quotes(char **args)
{
	int	len;
	int	*trg;
	int	index;

	index = 0;
	len = ft_str_tab_len(args);
	trg = (int *)malloc(sizeof(int) * (len + 1));
	while (args[index])
	{
		if (ft_str_contains(args[index], "\"", 0)
			|| ft_str_contains(args[index], "'", 0))
			trg[index] = 1;
		else
			trg[index] = 0;
		index++;
	}
	trg[index] = -1;
	return (trg);
}
