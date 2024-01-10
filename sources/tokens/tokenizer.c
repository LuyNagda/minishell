/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:16:57 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 07:01:27 by jbadaire         ###   ########.fr       */
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

static void ft_post_process_token_type(t_tokens *tmp)
{
	t_tokens *next;
	while (tmp)
	{
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
		tmp = tmp->next;
	}
}

static t_boolean is_word(char c)
{
	return (ft_is_alpha_num(c));
}

static void ft_split_to_tokens(t_minishell *shell)
{
	size_t current_position;
	char *sended;
	int tmp;

	sended = shell->sended_line;
	while (sended[0])
	{
		if (!is_word(sended[0]))
		{
			ft_add_back_token(&shell->parsing_cmd.tokens, ft_create_token(ft_substr(sended++, 0, 1), 1));
			continue;
		}
		current_position = 0;
		while (sended[current_position] && (is_word(sended[current_position])))
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
	ft_split_to_tokens(shell);
	ft_pre_process_token_type(shell->parsing_cmd.tokens);
	ft_post_process_token_type(shell->parsing_cmd.tokens);
}
