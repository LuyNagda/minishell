/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:32:12 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/09 14:07:25 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdlib.h"

t_tokens *ft_create_token(char *token, t_token_type token_type)
{
	t_tokens *tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->value = token;
	tokens->type = token_type;
	tokens->next = 0;
	tokens->previous = 0;
	return (tokens);
}

void ft_add_back_token(t_tokens **tokens_list, t_tokens *token)
{
	t_tokens *tmp;
	size_t pos;

	tmp = *tokens_list;
	pos = 1;
	if (!tmp || tmp->type == 0)
	{
		(*tokens_list)->type = token->type;
		(*tokens_list)->value = token->value;
		free(token);
		return;
	}
	while (tmp->next && pos++)
		tmp = tmp->next;
	token->previous = tmp;
	tmp->next = token;
}

void ft_delete_token(t_tokens **head, t_tokens *token)
{
	if (*head == NULL || token == NULL)
		return;
	if (*head == token)
		*head = token->next;
	if (token->next != NULL)
		token->next->previous = token->previous;
	if (token->previous != NULL)
		token->previous->next = token->next;
	if (token->value)
		free(token->value);
	if (token)
		free(token);
}

void ft_flush_tokens(t_tokens *tokens)
{
	t_tokens *tmp;

	while (tokens)
	{
		tmp = (tokens)->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}
