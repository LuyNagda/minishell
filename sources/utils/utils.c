/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:54:25 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/21 14:54:46 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*get_minishell(t_minishell *minishell)
{
	static t_minishell	*shell = NULL;

	if (shell == NULL && minishell != NULL)
		shell = minishell;

	return (shell);
}
