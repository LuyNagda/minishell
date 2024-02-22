/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:58:09 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/21 14:49:54 by lunagda          ###   ########.fr       */
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
	char		*str;
	t_env_map	*node;

	if (signum == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 0);
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		str = ft_strdup("130");
		if (!str)
			return;
		node = env_map_find_node(get_minishell(NULL)->env_map, "?");
		if (!node)
			return;
		free(node->value);
		node->value = str;
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
	if (sigaction(SIGINT, &sig, NULL) == -1
		|| sigaction(SIGQUIT, &sig, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
}
