#include <stdlib.h>

#include "minishell.h"
#include "string_utils.h"

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
