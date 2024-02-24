/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:36:19 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/24 17:50:19 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	ft_display_env_map(t_env_map *env_map)
{
	while (env_map)
	{
		printf("%s=%s\n", env_map->key, env_map->value);
		env_map = env_map->next_node;
	}
}

void	ft_display_env_array(char **env_array)
{
	size_t	i;

	i = 0;
	while (env_array[i])
	{
		printf("%s\n", env_array[i]);
		i++;
	}
}

void	ft_display_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		printf("type = {%d},", tokens->type);
		printf("				value = {%s},", tokens->value);
		printf("				pos = {%zu}\n", get_current_token_pos(tokens));
		if (!tokens->next)
			break ;
		tokens = tokens->next;
	}
}

void	print_args(t_commands *commands, size_t command_nb)
{
	int	index;

	index = 0;
	printf(" [%zu] -> Already Executed: %d\n",
		command_nb, commands->has_already_executed);
	printf(" [%zu] -> Ordered Position In List: %zu\n",
		command_nb, commands->position);
	printf("[%zu] -> Error During Creation : %d\n",
		command_nb, commands->error_during_creation);
	printf("[%zu] -> Is Built-in : %d\n",
		command_nb, commands->is_builtin);
	printf("[%zu] -> Input FD : %d\n",
		command_nb, commands->input_fd);
	printf("[%zu] -> Output FD : %d\n",
		command_nb, commands->output_fd);
	while (commands->args_quoted[index] != -1)
	{
		printf("Args quoted[%d]: %d\n", index, commands->args_quoted[index]);
		index++;
	}
}

void	ft_display_commands_list(t_commands *commands)
{
	size_t	command_nb;
	int		index;

	command_nb = 0;
	while (commands)
	{
		printf(" [%zu] -> Command Raw: %s\n [%zu] -> Command Name: %s\n",
			command_nb, commands->raw_command,
			command_nb, commands->arguments[0]);
		printf(" [%zu] -> Arguments (%zu)\n",
			command_nb, commands->arguments_amount);
		index = 0;
		while (commands->arguments && commands->arguments[index])
			printf("	[%s]\n", commands->arguments[index++]);
		print_args(commands, command_nb);
		printf(" \n\n-------------------------------\n\n");
		command_nb++;
		commands = commands->next_node;
	}
}
