/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:40:05 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/12 02:09:10 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"

/**
 * @brief Calculates the total length of the values in a linked list of tokens.
 *
 * This function traverses the linked list of tokens and calculates the total
 * length of the values in it by summing up the length of each token's value.
 *
 * @param tokens A pointer to the first token in the linked list.
 * @return The total length of the values in the linked list of tokens.
 */
size_t ft_tokens_len(t_tokens *tokens)
{
	size_t len;

	len = 0;
	while (tokens)
	{
		len += ft_strlen(tokens->value);
		tokens = tokens->next;
	}
	return (len);
}

/**
 * @brief Gets the total number of tokens in a linked list.
 *
 * This function traverses the linked list of tokens and counts the total
 * number of tokens in it.
 *
 * @param tokens A pointer to the first token in the linked list.
 * @return The total number of tokens in the linked list.
 */
size_t ft_get_tokens_amount(t_tokens *tokens)
{
	size_t amount;

	amount = 0;
	while (tokens)
	{
		amount++;
		tokens = tokens->next;
	}
	return (amount);
}

/**
 * @brief Gets the position of the current token in the linked list of tokens.
 *
 * @details This function calculates the position of the current token in the linked list
 * by counting the number of tokens that precede it.
 *
 * @param tokens A pointer to the current token in the linked list.
 * @return The position of the current token in the linked list.
 */
size_t get_current_token_pos(t_tokens *tokens)
{
	t_tokens *tmp;
	size_t amount_before;

	amount_before = 0;
	tmp = tokens;
	while (tmp && tmp->previous != 0)
	{
		tmp = tmp->previous;
		amount_before++;
	}
	return (amount_before);
}

size_t ft_get_tokens_type_amount(t_tokens *tokens, t_token_type tokenType)
{
	size_t amount;

	amount = 0;
	while (tokens)
	{
		if (tokens->type == tokenType)
			amount++;
		tokens = tokens->next;
	}
	return (amount);
}

long long ft_next_token_pos(t_tokens *tok, t_token_type type, long long start)
{
	long long pos;

	pos = start;
	while (start && tok)
	{
		start--;
		tok = tok->next;
	}
	while (tok)
	{
		if (tok->type == type)
			return (pos);
		pos++;
		tok = tok->next;
	}
	return (-1);
}

/**
 * @brief Gets the index in the original string corresponding to a given token position.
 *
 * This function calculates the index in the original string corresponding to the
 * given token position by traversing the linked list of tokens up to that position
 * and summing the lengths of their values.
 *
 * @param shell A pointer to the minishell structure.
 * @param token_pos The position of the token in the linked list.
 * @return The index in the original string corresponding to the token position.
 */
size_t get_index_from_token(t_minishell *shell, size_t token_pos)
{
	size_t len;
	size_t index;
	t_tokens *tmp;

	index = 0;
	len = 0;
	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		len += ft_strlen(tmp->value);
		tmp = tmp->next;
		index++;
		if (token_pos == index)
			break;
	}
	return len;
}