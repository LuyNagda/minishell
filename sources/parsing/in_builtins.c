/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:14:49 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/08 13:06:39 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"

int	in_builtins(char *command)
{
	char **split;

	split = ft_split(command, ' ');
	if (ft_str_equals(split[0], "clear")
		|| ft_str_equals(split[0], "cd")
		|| ft_str_equals(split[0], "pwd")
		|| ft_str_equals(split[0], "exit")
		|| ft_str_equals(split[0], "echo")
		|| ft_str_equals(split[0], "export")
		|| ft_str_equals(split[0], "unset")
		|| ft_str_equals(split[0], "env")
	)
	{
		ft_free_split(split);
		return (1);
	}
	ft_free_split(split);
	return (0);
}