/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:58:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/20 16:40:07 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
# include "minishell.h"
# include "put_utils.h"


int	g_signal_state;

static void handle_heredoc_signal(int signum)
{
	g_signal_state = signum;
}

static void handle_exit_signal(int signum)
{
	(void) signal;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void handle_signals(int signum)
{
	g_signal_state = signum;
	if (access(".here_doc", F_OK) == 0)
		handle_heredoc_signal(signum);
	else
		handle_exit_signal(signum);
}

void hook_exit_signal(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_signals;
	if (sigaction(SIGINT, &sig, NULL) == -1 || sigaction(SIGQUIT, &sig, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
}