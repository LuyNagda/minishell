/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:22:40 by lunagda           #+#    #+#             */
/*   Updated: 2024/01/18 13:13:39 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string_utils.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

// Managing all the redirection (duplicating pipes, output_fd with STDIN/STDOUT)
// Gestion de toutes les redirections (duplication des pipes, output_fd avec STDIN/STDOUT)
static void	redirections(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (command->position > 0 && !command->input_fd)
	{
		if (dup2(pipex->o_pipe[0], STDIN_FILENO) == -1)
			error_msg("DUP2 failed");
	}
	if (has_redirection(command, '<'))
	{
		redirection_parsing(command, "<");
		if (dup2(command->input_fd, STDIN_FILENO) == -1)
			error_msg("DUP2 failed");
		close(command->input_fd);
	}
	if (has_redirection(command, '>'))
	{
		redirection_parsing(command, ">");
		if (dup2(command->output_fd, STDOUT_FILENO) == -1)
			error_msg("DUP2 failed");
		close(command->output_fd);
	}
	else if (shell->command_amount != 1 && command->position < shell->command_amount - 1)
	{
		if (dup2(pipex->c_pipe[1], STDOUT_FILENO) == -1)
			error_msg("DUP2 failed");
	}
}

// Closing all the open pipes in child, checking if the command is builtin then running the builtin
// if not built_in, we execve the command passed as argument and give out appropriate error if fails.
// Fermeture de tous les pipes ouverts dans l'enfant, vérification si la commande est intégrée et exécution de l'intégration.
// si ce n'est pas le cas, nous exécutons la commande passée en argument et affichons l'erreur appropriée en cas d'échec.
static void	exec_command(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (command->position != 0)
		close(pipex->o_pipe[0]);
	close(pipex->c_pipe[0]);
	close(pipex->c_pipe[1]);
	if (command->is_builtin)
	{
		ft_dispatch_builtin(shell, command);
		exit(127);
	}
	if (execve(command->path, command->arguments, pipex->envp) == -1)
	{
		if (command->path == NULL)
			ft_printf("command not found: %s\n", command->arguments[0]);
		else
			ft_printf("%s: %s\n", strerror(errno), command->arguments[0]);
	}
	exit(EXIT_FAILURE);
}

void	child(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	redirections(shell, command, pipex);
	exec_command(shell, command, pipex);
}

// Initialising pipe and child. Child is initialised in the relating pid to his position.
// Closing current pipe 1 in the parent as it is not required once we write to it.
// Closing old pipe 0 when the command is not the first command or is the last command
// Lastly, assinging the current pipe 0 to the old pipe 0 to store it's value for next child
// Initialisation du tuyau et de l'enfant. L'enfant est initialisé dans le pid correspondant à sa position.
// Fermeture du tuyau 1 dans le parent car il n'est pas nécessaire une fois que l'on a écrit dessus.
// Fermeture de l'ancien tuyau 0 lorsque la commande n'est pas la première ou la dernière.
// Enfin, on assigne le current pipe 0 à l'old pipe 0 pour stocker sa valeur pour le prochain enfant.
void	exec_cmd_loop(t_minishell *shell, t_commands *command, t_pipex *pipex)
{
	if (pipe(pipex->c_pipe) == -1)
		error_msg("Pipe");
	pipex->pid[command->position] = fork();
	if (pipex->pid[command->position] < 0)
		error_msg("Fork");
	if (pipex->pid[command->position] == 0)
		child(shell, command, pipex);
	close(pipex->c_pipe[1]);
	if (pipex->o_pipe[0] != -1 || (command->position == shell->command_amount - 1))
		close(pipex->o_pipe[0]);
	if (!(command->position == shell->command_amount - 1))
		pipex->o_pipe[0] = pipex->c_pipe[0];
}

// Mallocing the pid with number of commands, assigning envp and initialising old pipe
// loop commands and run the function until the last command in the list
// close all the pipes used. After, waiting for all the children and getting status
// converting status code to string and assigning the status code
// Mallocing du pid avec le nombre de commandes, attribution de l'envp et initialisation de l'ancien pipe
// boucler les commandes et exécuter la fonction jusqu'à la dernière commande de la liste
// fermer tous les tuyaux utilisés. Ensuite, attente de tous les enfants et obtention du statut
// conversion du code d'état en chaîne de caractères et attribution du code d'état
void	exec_cmd(t_minishell *shell, t_commands *commands)
{
	t_pipex	pipex;

	pipex.pid = (int *)malloc(sizeof(int) * shell->command_amount);
	pipex.envp = env_map_to_array(shell->env_map);
	if (pipex.envp == NULL)
		return ;
	pipex.o_pipe[0] = -1;
	while (commands)
	{
		exec_cmd_loop(shell, commands, &pipex);
		commands = commands->next_node;
	}
	close(pipex.o_pipe[0]);
	close(pipex.c_pipe[0]);
	close(pipex.c_pipe[1]);
	pipex.index = 0;
	while (pipex.index < shell->command_amount)
		waitpid(pipex.pid[pipex.index++], &pipex.status, 0);
	pipex.status_string = ft_itoa(WEXITSTATUS(pipex.status));
	env_map_replace(shell->env_map, "?", pipex.status_string);
	free(pipex.status_string);
	ft_free_split(pipex.envp);
}
