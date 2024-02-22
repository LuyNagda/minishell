/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:32:12 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/19 12:30:39 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdlib.h"

t_tokens	*ft_create_token(char *token, t_token_type token_type)
{
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->value = token;
	tokens->type = token_type;
	tokens->next = 0;
	tokens->previous = 0;
	return (tokens);
}

void	ft_add_back_token(t_tokens **tokens_list, t_tokens *token)
{
	t_tokens	*tmp;
	size_t		pos;

	tmp = *tokens_list;
	pos = 1;
	if (!tmp || tmp->type == 0)
	{
		(*tokens_list)->type = token->type;
		(*tokens_list)->value = token->value;
		free(token);
		return ;
	}
	while (tmp->next && pos++)
		tmp = tmp->next;
	token->previous = tmp;
	tmp->next = token;
}

void	add_token_after(t_tokens **tokens, t_tokens *new_token, t_tokens *after)
{
	t_tokens	*tmp;

	if (after == NULL)
	{
		ft_add_back_token(tokens, new_token);
		return ;
	}
	tmp = after->next;
	after->next = new_token;
	new_token->previous = after;
	new_token->next = tmp;
	if (tmp)
		tmp->previous = new_token;
}

void	ft_free_token(t_tokens *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

void	ft_flush_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = (tokens)->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}
