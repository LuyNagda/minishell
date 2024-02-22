/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:20:38 by lunagda           #+#    #+#             */
/*   Updated: 2024/02/22 15:46:57 by lunagda          ###   ########.fr       */
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
		ft_putstr_fd("\n", 0);
		env_map_replace(get_minishell(NULL)->env_map, "?", "130");
		close(0);
	}
	if (signum == SIGQUIT)
	{
		env_map_replace(get_minishell(NULL)->env_map, "?", "131");
		ft_putstr_fd("\b\b  \b\b", 0);
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
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_heredoc_signals;
	if (sigaction(SIGINT, &sig, NULL) == -1
		|| sigaction(SIGQUIT, &sig, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
}
