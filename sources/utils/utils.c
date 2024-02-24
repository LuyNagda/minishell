/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:25 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/24 11:07:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "char_utils.h"

t_minishell	*get_minishell(t_minishell *minishell)
{
	static t_minishell	*shell = NULL;

	if (shell == NULL && minishell != NULL)
		shell = minishell;
	return (shell);
}

t_boolean	ft_str_is_only_whitespace(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (!ft_is_whitespace(str[index]))
			return (_false);
		index++;
	}
	return (_true);
}
