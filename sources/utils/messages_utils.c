/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:38:28 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/04 20:50:33 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_message	ft_init_messages(void)
{
	t_message	messages;

	messages.minishell_prefix = "\033[0;32m➜ \033[1;36m minishell :\033[0m ";
	messages.pipe_syntax_error = "⛔ Syntax error near unexpected token '|'\n";
	messages.double_pipe_error = "⛔ Syntax error near unexpected token '||' (Unsupported)\n";
	messages.quote_not_closed = "⛔ Quote is not closed.\n";
	messages.whitepipe_error = "⛔ Syntax error near unexpected token '|'. (WhitePipe) \n";
	return (messages);
}
