/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:36:19 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 14:15:42 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../dependencies/libft/.includes/ft_printf.h"

void	ft_display_env_map(t_env_map *env_map)
{
	while (env_map)
	{
		ft_printf("%s=%s\n", env_map->key, env_map->value);
		env_map = env_map->next_node;
	}
}

void	ft_display_env_array(char **env_array)
{
	size_t	i;

	i = 0;
	while (env_array[i])
	{
		ft_printf("%s\n", env_array[i]);
		i++;
	}
}

void	ft_display_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		ft_printf("type = {%d},\0", tokens->type);
		ft_printf("		value = {%s},\0",tokens->value);
		ft_printf("		pos = {%d}\n",get_current_token_pos(tokens));

		if (!tokens->next)
			break ;
		tokens = tokens->next;
	}
}

void	ft_display_commands_list(t_commands *commands)
{
	size_t	command_nb = 0;
	while (commands)
	{
		ft_printf(" [%i] -> Error During Creation : %i \n [%i] -> Command Raw: %s\n [%i] -> Command Name: %s\n",command_nb, commands->error_during_creation,command_nb, commands->raw_command,command_nb, commands->command_name);
		ft_printf(" [%i] -> Arguments (%i)\n", command_nb, commands->arguments_amount);
		int index = 0;
		while (commands->arguments[index])
			ft_printf("	|%s|\n", commands->arguments[index++]);
		ft_printf(" [%i] -> Mixed (%i)\n", command_nb, commands->arguments_amount + 1);
		index = 0;
		while (commands->mixed[index])
			ft_printf("	|%s|\n", commands->mixed[index++]);
		ft_printf(" [%i] -> Already Executed: %d\n", command_nb, commands->has_already_executed);
		ft_printf(" [%i] -> Ordered Position In List: %d\n", command_nb, commands->position);
		ft_printf(" \n\n-------------------------------\n\n");
		command_nb++;
		commands = commands->next_node;
	}
}