/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:15:13 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 03:21:36 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include <stdlib.h>

void	post_parsing(t_minishell *shell)
{
	char	last;
	char	*tmp;

	tmp = ft_strtrim(shell->parsing_cmd.latest_command, " ");
	free(shell->parsing_cmd.latest_command);
	shell->parsing_cmd.latest_command = tmp;
	free(tmp);
	tmp = NULL;
	last = ft_get_last_char_iw(shell->parsing_cmd.latest_command);
	if (last == '|')
	{
		tmp = ft_strdup(shell->parsing_cmd.latest_command);
		free(shell->parsing_cmd.latest_command);
		shell->parsing_cmd.latest_command = ft_substr(tmp, 0, ft_strlen(tmp) -1);
		free(tmp);
	}
	//ft_cmd_transform_env(shell);
}
