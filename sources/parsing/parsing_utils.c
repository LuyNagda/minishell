/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:49:31 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/26 15:58:52 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>

int	find_next_quote(char *str)
{
	int		index;

	index = 1;
	while (str[index])
	{
		if (str[index] == '\"' || str[index] == '\'')
			return (index);
		index++;
	}
	return (0);
}

int	find_unsual_things(char *str)
{
	char	*substr;

	substr = ft_substr(str, find_next_quote(str), ft_strlen(str));
	if (ft_str_contains(substr, "||", 0))
		return (free(substr), 1);
	if (ft_str_contains(substr, ";", 0))
		return (free(substr), 1);
	return (0);
}
