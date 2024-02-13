/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:58:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/13 16:52:47 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
#include <stdio.h>
#include <stdlib.h>
# include "minishell.h"

static void handle_ignore_signal(int signal)
{
	(void)signal;
}

void handle_ignored_signal(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_ignore_signal;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		return (perror("sigpipe"), exit(1));
}