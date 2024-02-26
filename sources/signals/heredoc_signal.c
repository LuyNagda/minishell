/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:20:38 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/26 15:59:27 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include "put_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "string_utils.h"

static void	handle_heredoc_signal(int signum)
{
	g_signal_state = signum;
	if (signum == SIGINT)
	{
		ft_putendl_fd("\n", 0);
		env_map_replace(get_minishell(NULL)->env_map, "?", "130");
	}
}

static void	handle_heredoc_signals(int signum)
{
	g_signal_state = signum;
	if (access(".here_doc", F_OK) == 0)
		handle_heredoc_signal(signum);
}

void	hook_heredoc_signal(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = handle_heredoc_signals;
	if (sigaction(SIGINT, &sig, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}
}
