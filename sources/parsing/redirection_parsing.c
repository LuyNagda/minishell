/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luynagda <luynagda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:42:21 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/18 09:38:10 by luynagda         ###   ########.fr       */
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
static void	remove_file_from_command(t_commands *command)
{
	int		i;
	int		j;
	char	**tmp;
	char	**result;

	i = 0;
	tmp = command->arguments;
	while (tmp[i] && ft_strncmp(tmp[i], ">", 1))
		i++;
	j = i;
	while (tmp[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i - 2));
	command->arguments_amount = i - 1;
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
void	out_redirection_parsing(t_commands *command)
{
	int			redirection;
	int			i;
	int			count;
	t_commands	*tmp;

	tmp = command;
	count = count_redirection(tmp, ">");
	while (count)
	{
		i = 0;
		redirection = has_redirection(tmp, '>');
		if (redirection)
		{
			while (tmp->arguments[i] && ft_strncmp(tmp->arguments[i], ">", 1))
				i++;
			if (redirection == 1)
				tmp->output_fd = open(tmp->arguments[++i], O_CREAT | O_RDWR | O_TRUNC, 0777);
			else if (redirection == 2)
				tmp->output_fd = open(tmp->arguments[++i], O_WRONLY | O_APPEND | O_CREAT, 0777);
			remove_file_from_command(tmp);
		}
		if (count > 1)
			close(command->output_fd);
		count--;
	}
}
