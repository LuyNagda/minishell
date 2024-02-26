/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:58:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/26 15:08:03 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string_utils.h>
#include <readline/readline.h>
#include <unistd.h>
#include "minishell.h"
#include "put_utils.h"

int	g_signal_state;

static void	handle_exit_signal(int signum)
{
	if (signum == SIGINT)
	{
		env_map_replace(get_minishell(NULL)->env_map, "?", "130");
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_signals(int signum)
{
	g_signal_state = signum;
	if (access(".here_doc", F_OK) != 0)
		handle_exit_signal(signum);
}

void	hook_exit_signal(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_signals;
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
