/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:36:19 by jbadaire          #+#    #+#             */
/*   Updated: 2023/12/04 22:35:31 by jbadaire         ###   ########.fr       */
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
		ft_printf("type = %d, value = %c\n", tokens->type, tokens->value);
		if (!tokens->next)
			break ;
		tokens = tokens->next;
	}
}