/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:27:22 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/22 13:36:03 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "string_utils.h"
#include "ft_printf.h"

static int	check_for_out_of_bounds(char *line)
{
	int	i;
	unsigned char c;

	i = 0;
	if (!line[i])
		return (1);
	while (line[i])
	{
		c = (unsigned char) line[i];
		if (c < 0 || c > 127)
			return (1);
		i++;
	}
	return (0);
}

static void	throw_env_error(t_minishell *shell)
{
	shell->envp = convert_path_to_array(shell->env_map);
	if (shell->envp == NULL)
		ft_printf("PATH has been unset. Only builtin commands can be executed.\n");
	else
		ft_free_split(shell->envp);
}

static void	ft_shell_loop(t_minishell *shell)
{
	char	*line;

	throw_env_error(shell);
	while (shell->is_running)
	{
		line = readline(shell->messages.minishell_prefix);
		if (check_for_out_of_bounds(line))
			return ;
		shell->sended_line = ft_strtrim(line, " ");
		free(line);
		if (pre_parsing(shell) != SUCCESS)
			continue;
		add_history(shell->sended_line);
		tokenize_input(shell);
		if(on_parse(shell) == SUCCESS)
		{
			if (post_parsing(shell) == SUCCESS)
				ft_dispatch_command(shell);
		}
		ft_flush_command_list(shell->commands);
		ft_flush_tokens(shell->parsing_cmd.tokens);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;

	(void) argc;
	(void) argv;
	shell.is_running = 1;
	shell.messages = ft_init_messages();
	shell.env_map = env_map_init();
	if (shell.env_map)
		env_array_to_map(&shell, &shell.env_map, env);
	ft_shell_loop(&shell);
	env_map_flush(shell.env_map);
	rl_clear_history();
	rl_clear_message();
	rl_clear_visible_line();
	rl_clear_pending_input();
	return (0);
}
