/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:10:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/09 18:01:21 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include <stdlib.h>
#include <stdio.h>

void	error_msg(char *string)
{
	perror(string);
	exit(EXIT_FAILURE);
}


char	**trim_command_list(char **command_list)
{
	int		i;
	int		nb;
	char	**result;

	i = 0;
	nb = 0;
	while (command_list[nb])
		nb++;
	result = (char **)malloc((nb + 1) * sizeof(char *));
	while (i < nb)
	{
		result[i] = ft_strdup(ft_strtrim(command_list[i], " >"));
		free(command_list[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}
