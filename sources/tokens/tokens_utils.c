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
 * @brief Gets the total number of tokens in a linked list.
 *
 * This function traverses the linked list of tokens and counts the total
 * number of tokens in it.
 *
 * @param tokens A pointer to the first token in the linked list.
 * @return The total number of tokens in the linked list.
 */
size_t	ft_get_tokens_amount(t_tokens *tokens)
{
	size_t	amount;

	amount = 0;
	while (tokens)
	{
		amount++;
		tokens = tokens->next;
	}
	return (amount);
}

/**
 * @brief Gets the pos of the current token in the llist of tokens.
 *
 * @details This function calc the pos of the current token in the llist
 * by counting the number of tokens that precede it.
 *
 * @param tokens A pointer to the current token in the llist.
 * @return The pos of the current token in the llist.
 */
size_t	get_current_token_pos(t_tokens *tokens)
{
	t_tokens	*tmp;
	size_t		amount_before;

	amount_before = 0;
	tmp = tokens;
	while (tmp && tmp->previous != 0)
	{
		tmp = tmp->previous;
		amount_before++;
	}
	return (amount_before);
}

/**
 * @brief Gets the i in the src string corresponding to a given token pos.
 *
 * This function calc the index in the original string corresponding to the
 * given token pos by traversing the llist of tokens up to that position
 * and summing the lengths of their values.
 *
 * @param shell A pointer to the minishell structure.
 * @param token_pos The position of the token in the linked list.
 * @return The index in the src string corresponding to the token pos.
 */
size_t	get_index_from_token(t_minishell *shell, size_t token_pos)
{
	size_t		len;
	size_t		index;
	t_tokens	*tmp;

	index = 0;
	len = 0;
	tmp = shell->parsing_cmd.tokens;
	while (tmp)
	{
		len += ft_strlen(tmp->value);
		tmp = tmp->next;
		index++;
		if (token_pos == index)
			break ;
	}
	return (len);
}