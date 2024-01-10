/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:16:57 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 17:04:10 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/ft_printf.h"
#include <stdlib.h>

static void ft_pre_process_token_type(t_tokens *tmp)
{
	while (tmp)
	{
		if (ft_str_equals(tmp->value, "\'"))
			tmp->type = SIMPLE_QUOTE;
		else if (ft_str_equals(tmp->value, "\""))
			tmp->type = DOUBLE_QUOTE;
		else if (ft_str_equals(tmp->value, "|"))
			tmp->type = PIPE;
		else if (ft_str_equals(tmp->value, ">"))
			tmp->type = REDIRECT_OUT;
		else if (ft_str_equals(tmp->value, "<"))
			tmp->type = REDIRECT_IN;
		else if (ft_is_whitespace(tmp->value[0]))
			tmp->type = SPACE;
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}

static t_boolean ft_token_is_in_quote(t_minishell *shell, char *rebuilded_string, size_t token_pos)
{
	size_t len = get_index_from_token(shell, token_pos);
	return (ft_index_is_in_quotes(rebuilded_string, len));
}

static void post_process_redirections(t_tokens *tmp)
{
	t_tokens	*next;

	if (tmp->type == REDIRECT_OUT && tmp->next && tmp->next->type == REDIRECT_OUT)
	{
		tmp->type = REDIRECT_OUT_DOUBLE;
		free(tmp->value);
		tmp->value = ft_strdup(">>");
		next = tmp->next->next;
		free(tmp->next);
		tmp->next = next;
	}
	else if (tmp->type == REDIRECT_IN && tmp->next && tmp->next->type == REDIRECT_IN)
	{
		tmp->type = REDIRECT_IN_DOUBLE;
		free(tmp->value);
		tmp->value = ft_strdup("<<");
		next = tmp->next->next;
		free(tmp->next);
		tmp->next = next;
	}
}

static void ft_post_process_token_type(t_tokens *tmp, t_minishell *shell)
{
	char		*rebuilded;

	rebuilded = rebuild_string_from_token(shell);
	while (tmp)
	{
		post_process_redirections(tmp);
		tmp = tmp->next;
	}
	if (rebuilded)
		free(rebuilded);
}

static void ft_split_to_tokens(t_minishell *shell, size_t current_position, int tmp)
{
	char *sended;

	sended = shell->sended_line;

	while (sended[0])
	{
		if (!ft_is_alpha_num(sended[0]))
		{
			ft_add_back_token(&shell->parsing_cmd.tokens, ft_create_token(ft_substr(sended++, 0, 1), 1));
			continue;
		}
		current_position = 0;
		while (sended[current_position] && ft_is_alpha_num((sended[current_position])))
			current_position++;
		ft_add_back_token(&shell->parsing_cmd.tokens, ft_create_token(ft_substr(sended, 0, current_position), 1));
		tmp = 0;
		while (current_position > tmp++)
			sended++;
	}
}

void tokenize_input(t_minishell *shell)
{
	shell->parsing_cmd.tokens = ft_create_token(0, 0);
	ft_split_to_tokens(shell, 0, 0);
	ft_pre_process_token_type(shell->parsing_cmd.tokens);
	ft_post_process_token_type(shell->parsing_cmd.tokens, shell);
}
