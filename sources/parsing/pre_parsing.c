/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:15:16 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 03:34:55 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/put_utils.h"
#include "../../dependencies/libft/.includes/char_utils.h"
#include <stdlib.h>

static int	is_only_space(char *line)
{
	int	index;
	int	space_amount;

	index = 0;
	space_amount = 0;
	while (line[index])
	{
		if (ft_is_space(line[index]))
			space_amount++;
		index++;
	}
	return (space_amount == index);
}

static int	is_valid_line(char *line)
{
	return (line && !is_only_space(line) && line[0] != '\0');
}

/**
 * @brief Pre-parses the input line to check for syntax errors.
 *
 * This function performs pre-parsing on the input line in the `shell` structure
 * to check for various syntax errors. It returns a parsing result indicating
 * the outcome of the pre-parsing operation.
 *
 * @param shell The Minishell structure containing the input line.
 * @return The parsing result indicating the outcome of the pre-parsing operation.
 */
t_parsing_result pre_parsing(t_minishell *shell)
{
	if (!shell->sended_line || !is_valid_line(shell->sended_line))
		return (free(shell->sended_line), INVALID_INPUT);
	if (ft_str_contains(shell->sended_line, "||", 0))
		return (ft_putstr_fd(shell->messages.double_pipe_error, 2), free(shell->sended_line), INVALID_INPUT);
	if (ft_get_first_char_iw(shell->sended_line) == '|' || ft_get_last_char_iw(shell->sended_line) == '|')
		return (ft_putstr_fd(shell->messages.pipe_syntax_error, 2), free(shell->sended_line), INVALID_INPUT);
	if (!ft_quote_is_closed(shell->sended_line))
		return (ft_putstr_fd(shell->messages.quote_not_closed, 2), free(shell->sended_line), INVALID_INPUT);
	ft_replace_whitespace(shell->sended_line, ' ');
	return (SUCCESS);
}