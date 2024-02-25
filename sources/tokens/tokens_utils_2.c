/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:32:27 by luynagda          #+#    #+#             */
/*   Updated: 2024/02/22 20:32:28 by luynagda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "string_utils.h"

void	ft_delete_token(t_tokens **head, t_tokens *token)
{
	if (*head == NULL || token == NULL)
		return ;
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

void	delete_prev_token(t_minishell *shell, t_tokens *current)
{
	t_tokens	*prev;

	if (current->previous)
	{
		prev = current->previous;
		free(prev->value);
		prev->value = NULL;
		ft_delete_token(&shell->parsing_cmd.tokens, prev);
	}
}

void	add_space_token(t_minishell *shell, t_tokens *current)
{
	t_tokens	*space_token;

	space_token = ft_create_token(ft_strdup(" "), _SPACE);
	if (space_token == NULL)
		return ;
	add_token_after(&shell->parsing_cmd.tokens, space_token, current);
}
