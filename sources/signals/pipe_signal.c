/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:05:26 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/19 09:27:30 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void	handle_pipe_signal(int signum)
{
	(void)signum;
	get_minishell(NULL)->is_running = _false;
	env_map_find_node(get_minishell(NULL)->env_map, "?")->value = "1";
}

void	hook_pipe_signal(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_pipe_signal;
	if (sigaction(SIGPIPE, &sig, NULL) == -1)
		return (perror("sigaction"), exit(1));
}