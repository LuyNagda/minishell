/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:40:05 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/04 21:40:54 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

size_t	ft_get_tokens_type_amount(t_tokens *tokens, t_token_type tokenType)
{
	size_t	amount;

	amount = 0;
	while (tokens)
	{
		if (tokens->type == tokenType)
			amount++;
		tokens = tokens->next;
	}
	return (amount);
}

long long	ft_next_token_pos(t_tokens *tok, t_token_type type, long long start)
{
	long long	pos;

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