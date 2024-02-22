/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:19:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/21 12:47:50 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <libft.h>

#include "minishell.h"
#include "put_utils.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_has_only_whitespace_between_pipes(t_minishell *shell)
{
	t_tokens	*tmp;
	t_boolean	is_after_pipe;
	t_boolean	only_space;

	is_after_pipe = _false;
	only_space = _true;
	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (only_space && is_after_pipe)
				return (1);
			is_after_pipe = _true;
			only_space = _true;
		}
		else if (is_after_pipe)
		{
			if (tmp->type != _SPACE)
				only_space = _false;
		}
		tmp = tmp->next;
	}
	return (0);
}

t_parsing_result	on_parse(t_minishell *shell)
{
	if (ft_has_only_whitespace_between_pipes(shell) != 0)
		return (ft_putstr_fd(shell->messages.whitepipe_error, 2), \
			free(shell->sended_line), INVALID_INPUT);
	treat_variable_keys(shell);
	append_quoted(&shell->parsing_cmd.tokens);
	return (SUCCESS);
}
