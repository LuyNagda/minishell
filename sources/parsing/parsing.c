/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:06:13 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/04 15:19:03 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/put_utils.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include <stdlib.h>

static void	ft_set_tokens_attributes(t_tokens *tmp)
{
	while (tmp)
	{
		if (tmp->value == '\'')
			tmp->type = SIMPLE_QUOTE;
		else if (tmp->value == '\"')
			tmp->type = DOUBLE_QUOTE;
		else if (tmp->value == '|')
			tmp->type = PIPE;
		else if (tmp->value == '>')
		{
			if (tmp->next->value == '>')
			{
				tmp->type = REDIRECT_IN_DOUBLE;
				tmp->next->type = REDIRECT_IN_DOUBLE;
				tmp->next = tmp->next->next;
			}
			else
				tmp->type = REDIRECT_IN;
		}
		else if (tmp->value == '<')
		{
			if (tmp->next->value == '<')
			{
				tmp->type = REDIRECT_OUT_DOUBLE;
				tmp->next->type = REDIRECT_OUT_DOUBLE;
				tmp->next = tmp->next->next;
			}
			else
				tmp->type = REDIRECT_OUT;
		}
		else if (ft_is_whitespace(tmp->value))
			tmp->type = SPACE;
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}

static void	ft_tokenize(t_minishell *shell)
{
	size_t		index;
	t_tokens	*null_token;

	index = 0;
	null_token = ft_create_token(0, 0);
	if (!null_token)
		return ;
	shell->parsing_cmd.tokens = null_token;
	while (shell->sended_line[index])
	{
		ft_add_black_token(&shell->parsing_cmd.tokens, \
		ft_create_token(shell->sended_line[index++], 1));
	}
	ft_add_black_token(&shell->parsing_cmd.tokens, ft_create_token('|', PIPE));
	ft_default_cmd_struct(shell, _false);
	ft_set_tokens_attributes(shell->parsing_cmd.tokens);
}

static int	ft_has_whitepipe(t_minishell *shell)
{
	char		*command;

	ft_concat_tokens(shell, _false);
	while (shell->parsing_cmd.latest_command != NULL)
	{
		if (!ft_quote_is_closed(shell->parsing_cmd.latest_command))
			ft_concat_quoted_pipes(shell, 0);
		command =  shell->parsing_cmd.latest_command;
		if (ft_str_only_whitespace(command))
		{
			ft_putstr_fd(shell->messages.whitepipe_error, 2);
			return (free(command), ft_default_cmd_struct(shell, _false), 2);
		}
		free(command);
		shell->parsing_cmd.latest_command = NULL;
		ft_concat_tokens(shell, _false);
	}
	return (ft_default_cmd_struct(shell, _false), 0);
}

void	parse_input(t_minishell *shell)
{
	if (ft_str_contains(shell->sended_line, "||", 0, 0))
		return (ft_putstr_fd(shell->messages.double_pipe_error, 2), free(shell->sended_line));
	if (ft_get_first_char_iw(shell->sended_line) == '|' || ft_get_last_char_iw(shell->sended_line) == '|')
		return (ft_putstr_fd(shell->messages.pipe_syntax_error, 2), free(shell->sended_line));
	if (!ft_quote_is_closed(shell->sended_line))
		return (ft_putstr_fd(shell->messages.quote_not_closed, 2), free(shell->sended_line));
	ft_tokenize(shell);
	if (ft_has_whitepipe(shell) != 0)
		return (free(shell->sended_line));
	//ft_dispatch_commands(shell);
	//free(shell->sended_line);
}
