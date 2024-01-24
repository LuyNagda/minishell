/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:25:50 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/24 15:30:57 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_string_in_quotes(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (1);
	return (0);
}

static char	**populate_export_with_value(t_commands *command, int *i, int *has_equal)
{
	char	**export;

	export = (char **)malloc(sizeof(char *) * 3);
	if (!export)
		return (NULL);
	export[0] = ft_strtrim(command->arguments[*i], "=");
	export[1] = ft_strtrim(command->arguments[*i + 1], "\"");
	export[2] = 0;
	*has_equal = 1;
	*i = *i + 2;
	return (export);
}

static char **populate_export_without_value(t_commands *command, int *i, int *has_equal)
{
	char	**export;

	export = (char **)malloc(sizeof(char *) * 3);
	export[0] = ft_strtrim(command->arguments[*i], "=");
	export[1] = ft_strdup("");
	export[2] = 0;
	*has_equal = 1;
	*i = *i + 1;
	return (export);
}

static char **populate_export(t_commands *command, int *i, int *has_equal)
{
	char	**export;

	export = ft_split(command->arguments[*i], '=');
	if (!export[1])
	{
		ft_free_split(export);
		export = (char **)malloc(sizeof(char *) * 3);
		export[0] = ft_strdup(command->arguments[*i]);
		export[1] = ft_strdup("");
		export[2] = 0;
		*has_equal = 0;
	}
	else
		*has_equal = 1;
	*i = *i + 1;
	return (export);
}

char	**get_export_values(t_commands *command, int *i, int *has_equal)
{
	char	**export;

	if (!(command->arguments[*i]))
		return (NULL);
	if (ft_str_contains(command->arguments[*i], "=",
		ft_strlen(command->arguments[*i]) - 1)
		&& ft_string_in_quotes(command->arguments[*i + 1]))
		return (populate_export_with_value(command, i, has_equal));
	else if (ft_str_contains(command->arguments[*i], "=",
		ft_strlen(command->arguments[*i]) - 1)
		&& !ft_string_in_quotes(command->arguments[*i + 1]))
		return (populate_export_without_value(command, i, has_equal));
	else
		return (populate_export(command, i, has_equal));
}
