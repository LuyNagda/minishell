/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/18 13:09:34 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "string_utils.h"
#include <stdio.h>

// Counting the number of redirections in the command
// Compter le nombre de redirections dans la commande
static int	count_redirection(t_commands *command, char *character)
{
	int		i;
	int		count;
	char	**tmp;

	i = 0;
	count = 0;
	tmp = command->arguments;
	while (tmp[i])
	{
		if (!ft_strncmp(tmp[i], character, 1))
			count++;
		i++;
	}
	return (count);
}

// Removing the file from command arguments once it's opened
// Suppression du fichier des arguments de commande une fois qu'il a été ouvert
static void	remove_file_from_command(t_commands *command, char *character)
{
	int		i;
	int		j;
	char	**tmp;
	char	**result;

	i = 0;
	tmp = command->arguments;
	while (tmp[i] && ft_strncmp(tmp[i], character, 1))
		i++;
	j = i;
	while (tmp[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i - 1));
	command->arguments_amount = i - 2;
	i = 0;
	while (i < j)
	{
		result[i] = ft_strdup(tmp[i]);
		i++;
	}
	while (tmp[j + 2])
	{
		result[i] = ft_strdup(tmp[j + 2]);
		i++;
		j++;
	}
	result[i] = 0;
	ft_free_split(command->arguments);
	command->arguments = result;
}

static int	has_multiple_redirection(t_commands *command, char *character)
{
	if (!ft_strncmp(">", character, 1))
		return (has_redirection(command, '>'));
	else
		return (has_redirection(command, '<'));
}

// Getting the count of redirections and looping for that many times
// Check for which redirection and increment i to the redirection
// Open the file with append if ">>" else open with truncate
// Removing the opened file from the argument list
// Closing the fd if the file is not the last redirection
// Obtenir le nombre de redirections et tourner en boucle autant de fois que nécessaire
// Vérifier pour quelle redirection et incrémenter i à la redirection
// Ouvrir le fichier avec append if ">>" else open with truncate
// Suppression du fichier ouvert de la liste des arguments
// Fermer le fd si le fichier n'est pas la dernière redirection
void	redirection_parsing(t_commands *command, char *character)
{
	int			redirection;
	int			i;
	int			count;
	t_commands	*tmp;

	tmp = command;
	count = count_redirection(tmp, character);
	while (count)
	{
		i = 0;
		redirection = has_multiple_redirection(tmp, character);
		if (redirection)
		{
			while (tmp->arguments[i] && ft_strncmp(tmp->arguments[i], character, 1))
				i++;
			if (!ft_strncmp(">", character, 1))
			{
				if (redirection == 1)
					tmp->output_fd = open(tmp->arguments[++i], O_CREAT | O_RDWR | O_TRUNC, 0777);
				else
					tmp->output_fd = open(tmp->arguments[++i], O_WRONLY | O_APPEND | O_CREAT, 0777);
			}
			else
			{
				if (redirection == 1)
					tmp->input_fd = open(tmp->arguments[++i], O_RDONLY);
				else
					tmp->input_fd = 0;
			}
			remove_file_from_command(tmp, character);
		}
		if (count > 1)
			close(command->output_fd);
		count--;
	}
}
