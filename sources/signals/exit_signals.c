/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:58:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/13 16:23:14 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
# include "minishell.h"
# include "put_utils.h"

static void handle_exit(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void handle_exit_signal(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_exit;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		return (perror("sigaction"), exit(1));
}