/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:35:26 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 07:54:42 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/string_utils.h"
#include <stdlib.h>


/**
 * @brief Rebuilds a string from the tokens stored in the minishell structure.
 *
 * This function concatenates the values of tokens in the minishell's parsing command
 * to reconstruct the original command string.
 *
 * @param shell A pointer to the minishell structure.
 * @return A dynamically allocated string containing the reconstructed command.
 *         The caller is responsible for freeing the memory allocated for the string.
 */
char	*rebuild_string_from_token(t_minishell *shell)
{
	t_tokens	*tokens;
	char		*str_1;
	char		*str_2;

	tokens = shell->parsing_cmd.tokens;
	str_1 = ft_strdup("");
	while (tokens && tokens->value)
	{
		str_2 = ft_strjoin(str_1, tokens->value);
		free(str_1);
		str_1 = ft_strdup(str_2);
		free(str_2);
		tokens = tokens->next;
	}
	return (str_1);
}