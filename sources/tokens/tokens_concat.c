/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:35:26 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/15 20:02:47 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/memory_utils.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include <stdlib.h>

static size_t	ft_how_char(t_tokens *tokens, t_token_type until_type)
{
	size_t	char_amount;

	char_amount = 1;
	while (tokens && (tokens->type != until_type))
	{
		tokens = tokens->next;
		if (tokens->type == REDIRECT_IN_DOUBLE || tokens->type == REDIRECT_OUT_DOUBLE)
			char_amount++;
		char_amount++;
	}
	return (char_amount);
}

static void	ft_fill_token(t_tokens *tokens, t_token_type type, char *str)
{
	size_t	index;

	index = 0;
	while (tokens)
	{
		if (tokens->type == REDIRECT_OUT_DOUBLE || tokens->type == REDIRECT_IN_DOUBLE)
			str[index++] = tokens->value;
		str[index++] = tokens->value;
		if (!tokens->next)
			break ;
		tokens = tokens->next;
		if (tokens->type == type)
			break ;
	}
}

char	*ft_concat_tokens_util_type(t_tokens *tokens, size_t start_pos, t_token_type type)
{
	char		*str;
	t_tokens	*tmp;
	size_t		char_amount;

	tmp = tokens;
	while (tmp && start_pos--)
		tmp = tmp->next;
	char_amount = ft_how_char(tmp, type);
	str = ft_calloc(char_amount, sizeof(char));
	if (!str)
		return (NULL);
	ft_fill_token(tmp, type, str);
	return (str);
}

char	*ft_concat_tokens(t_minishell *shell, t_boolean reset_values)
{
	long long	n_start;
	t_commands	*commands;

	commands = &shell->commands;
	if (commands->next_start == -1 || !commands->tokens || ft_get_tokens_amount(commands->tokens) == 0)
		return (NULL);
	if (reset_values)
		ft_default_cmd_struct(shell, _false);
	commands->latest_command = ft_concat_tokens_util_type(commands->tokens, commands->last_end, PIPE);
	commands->last_end += (ft_strlen(commands->latest_command) + 1);
	n_start = ft_next_token_pos(commands->tokens, PIPE, (long long)commands->last_end);
	if (n_start == -1)
		commands->next_start = -1;
	else
		commands->next_start = n_start;
	return (commands->latest_command);
}

void	ft_concat_quoted_pipes(t_minishell *shell, char *final_str)
{
	char	*add_pipe;
	char	*tmp;

	if (shell->commands.latest_command == NULL)
		return ;
	if (ft_quote_is_closed(shell->commands.latest_command))
		add_pipe = ft_strdup(shell->commands.latest_command);
	else
		add_pipe = ft_strjoin(shell->commands.latest_command, "|");
	free(shell->commands.latest_command);
	if (!final_str)
		final_str = ft_strdup(add_pipe);
	else
	{
		tmp = ft_strdup(final_str);
		final_str = ft_strjoin(tmp, add_pipe);
		free(tmp);
	}
	free(add_pipe);
	if (ft_quote_is_closed(final_str))
		shell->commands.latest_command = final_str;
	else
	{
		ft_concat_tokens(shell, _false);
		ft_concat_quoted_pipes(shell, final_str);
	}
}