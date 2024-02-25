/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:27:22 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/25 18:21:30 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "string_utils.h"
#include "libft.h"

static int	check_for_out_of_bounds(char *line)
{
	int				i;
	unsigned char	c;

	i = 0;
	if (!line[i])
		return (0);
	while (line[i])
	{
		c = (unsigned char) line[i];
		if (c <= 0 || c > 127)
			return (1);
		i++;
	}
	return (0);
}

static void	tokenize_and_run(t_minishell *shell)
{
	tokenize_input(shell);
	if (on_parse(shell) == SUCCESS)
	{
		if (post_parsing(shell) == SUCCESS)
			ft_dispatch_command(shell);
		ft_flush_command_list(shell->commands);
	}
	ft_flush_tokens(shell->parsing_cmd.tokens);
	if (shell->sended_line)
		free(shell->sended_line);
}

static void	ft_shell_loop(t_minishell *shell)
{
	char	*line;

	while (shell->is_running)
	{
		hook_signal_on_start();
		shell->commands = NULL;
		line = readline(shell->messages.minishell_prefix);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (check_for_out_of_bounds(line))
			return ;
		shell->sended_line = ft_strtrim(line, " ");
		if (!shell->sended_line)
			break ;
		add_history(shell->sended_line);
		free(line);
		if (pre_parsing(shell) != SUCCESS)
			continue ;
		tokenize_and_run(shell);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;
	t_env_map	*node;
	int			status_code;

	(void) argc;
	(void) argv;
	shell.is_running = 1;
	shell.messages = ft_init_messages();
	env_map_init(&shell);
	if (&shell.env_map)
		env_array_to_map(&shell, &shell.env_map, env);
	node = env_map_find_node(shell.env_map, "?");
	get_minishell(&shell);
	ft_shell_loop(&shell);
	status_code = ft_atoi(node->value);
	env_map_flush(shell.env_map);
	rl_clear_history();
	rl_clear_message();
	rl_clear_visible_line();
	rl_clear_pending_input();
	return (status_code);
}
