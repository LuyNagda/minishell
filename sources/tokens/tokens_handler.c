/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:32:12 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/11 19:30:41 by jbadaire         ###   ########.fr       */
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
		return; // Rien à faire si la liste est vide ou le node à supprimer est null

	// Cas où le node à supprimer est le premier de la liste
	if (*head == token)
		*head = token->next;

	// Gérer la node précédent si le node à supprimer n'est pas le dernier
	if (token->next != NULL)
		token->next->previous = token->previous;

	// Gérer la node suivant si le node à supprimer n'est pas le premier
	if (token->previous != NULL)
		token->previous->next = token->next;

	if (token)
		free(token); // Libérer la mémoire du node à supprimer
}

void ft_flush_tokens(t_tokens *tokens)
{
	t_tokens *tmp;

	while (tokens)
	{
		tmp = (tokens)->next;
		free(tokens);
		tokens = tmp;
	}
}