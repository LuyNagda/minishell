/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:13:08 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/19 10:50:44 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
#include <stdio.h>
#include "put_utils.h"
# include "minishell.h"

static void handle_heredoc_signal(int signum)
{
	ft_putstr_fd("\b\b  \b\b", 0);
	if (signum != SIGINT)
		return;
	ft_putstr_fd("\n", 0);
	free_and_exit(get_minishell(NULL), get_minishell(NULL)->pipex, 1);
}


void hook_heredoc_signal(t_minishell *shell)
{
	struct sigaction sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_heredoc_signal;
	if (sigaction(SIGINT, &sig, NULL) == -1 || sigaction(SIGQUIT, &sig, NULL) == -1) {
		perror("sigaction");
		shell->is_running = _false;
	}
}