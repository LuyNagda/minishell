/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:45:39 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/10 07:36:00 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../dependencies/libft/.includes/boolean.h"
# include <stddef.h>

extern int	g_status_code;

typedef enum e_token
{
	WORD = 1,
	SPACE = 2,
	PIPE = 3,
	REDIRECT_IN = 4,
	REDIRECT_IN_DOUBLE = 5,
	REDIRECT_OUT = 6,
	REDIRECT_OUT_DOUBLE = 7,
	DOUBLE_QUOTE = 8,
	SIMPLE_QUOTE = 9,
}	t_token_type;

typedef enum e_parsing_result
{
	INVALID_INPUT,
	ERROR,
	SUCCESS
}	t_parsing_result;

typedef struct s_tokens
{
	t_token_type	type;
	char			*value;
	struct s_tokens	*previous;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_parsing_cmd
{
	t_tokens	*tokens;
	char		*latest_command;
}				t_parsing_cmd;

typedef struct s_commands
{
	char				*raw_command;
	char				*command_name;
	char				**arguments;
	char				**mixed;
	size_t				position;
	size_t				arguments_amount;
	t_boolean			has_already_executed;
	t_boolean			error_during_creation;
	struct	s_commands	*next_node;
}						t_commands;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_equal;
	int				is_system;
	int				is_immutable;
	struct s_env	*next_node;
}					t_env_map;

typedef struct s_message
{
	char		*minishell_prefix;
	char		*quote_not_closed;
	char		*pipe_syntax_error;
	char		*double_pipe_error;
	char		*whitepipe_error;

}				t_message;

typedef struct s_pipex
{
	int		index;
	int		status;
	int		sub_process_pid;
	int		c_pipe[2];
	int		o_pipe[2];
	int		infile;
	int		outfile;
	char	**path_array;
	char	*path;
	char	**command_list;
	char	*temp;
}			t_pipex;

typedef struct s_minishell
{
	t_boolean		is_running;
	t_message		messages;

	char			*sended_line;
	t_parsing_cmd	parsing_cmd;
	t_commands		*commands;
	size_t			command_amount;

	t_env_map		*env_map;
	char			**envp;

	t_pipex			*pipex;
}					t_minishell;

/* *****************************************************/
/* ******************** BUILTIN ************************/
/* *****************************************************/
int			ft_dispatch_builtin(t_minishell *shell, t_commands *command);
void		exec_export(t_minishell *shell, t_commands *command);
int			exec_unset(t_minishell *shell, t_commands *command);
void		exec_echo(t_minishell *shell, t_commands *commands);
int			exec_pwd(t_minishell *shell);
int			exec_cd(t_minishell *shell, t_commands *command);
int			exec_env(t_minishell *shell);
int			exec_exit(t_minishell *shell);
int			exec_clear(void);
/* *****************************************************/
/* ********************* EXEC **************************/
/* *****************************************************/

void		ft_dispatch_command(t_minishell *shell);
void		exec_cmd(t_minishell *shell, t_commands *command);
int			is_builtins(t_commands *command);
char		**convert_path_to_array(t_env_map *env_map);
char		*find_command(char *command, char **path_array);
void		exec_redirection(t_minishell *shell, char *line);

/* *****************************************************/
/* ********************** ENV **************************/
/* *****************************************************/

t_env_map	*env_map_init(char **env_array);
t_env_map	*ft_create_env_node(char *k, char *v, int has_equals, int is_system);
t_env_map	*env_map_add_back(t_env_map **env_map, t_env_map *new_node, int is_immutable);
t_env_map	*env_map_remove_from_key(t_env_map *env_map, char *key);
t_env_map	*env_map_replace(t_env_map *env_map, char *key, char *value);
t_env_map	*env_map_find_node(t_env_map *env_map, char *key);
t_env_map	*env_array_to_map(t_env_map **env_map, char **env);

char		**env_map_to_array(t_env_map *env_map);
char		*env_map_get_key(t_env_map *env_map, size_t node_pos);
void		env_map_flush(t_env_map *env_map);

size_t		env_map_get_size(t_env_map *env_map);

/* *****************************************************/
/* ******************** COMMANDS ***********************/
/* *****************************************************/

size_t		ft_get_numbers_of_commands(t_commands *commands_list);
t_commands	*ft_get_command_from_pos(t_commands *command_list, size_t command_node_pos);
t_commands	*ft_add_command(t_commands **commands, t_commands *new_node);

t_commands	*ft_command_list_init();
t_commands	*ft_create_command_node(char *cmd);
void		ft_flush_command_list(t_commands *list);

void		*ft_populate_command_list(t_minishell *shell);

/* *****************************************************/
/* ******************** PARSING ************************/
/* *****************************************************/

t_parsing_result	pre_parsing(t_minishell *shell);
t_parsing_result	on_parse(t_minishell *shell);
void				post_parsing(t_minishell *shell);


/* *****************************************************/
/* ******************** TOKENS *************************/
/* *****************************************************/

void		tokenize_input (t_minishell *shell);
t_tokens	*ft_create_token(char *token, t_token_type token_type);
void		ft_add_back_token(t_tokens **tokens_list, t_tokens *token);
void		ft_flush_tokens(t_tokens *tokens);
size_t		get_current_token_pos(t_tokens *tokens);

char		*rebuild_string_from_token(t_minishell *shell);
void		ft_concat_quoted_pipes(t_minishell *shell, char *final_str);

size_t		ft_tokens_len(t_tokens *tokens);
size_t		ft_get_tokens_amount(t_tokens *tokens);
size_t		ft_get_tokens_type_amount(t_tokens *tokens, t_token_type tokenType);
long long	ft_next_token_pos(t_tokens *tok, t_token_type type, long long start);

/* *****************************************************/
/* ********************* UTILS *************************/
/* *****************************************************/

int			ft_quote_is_closed(const char *line);
int			ft_index_is_in_quote(const char *line, size_t pos, char quote);
int			ft_index_is_in_quotes(const char *line, size_t pos);
int			ft_quote_is_closed_range(const char *line, size_t start, size_t end);
int			ft_str_equals(const char *str1, const char *str2);
int			ft_str_index_of(const char *src, const char *search, size_t *start_at, size_t starting_search);
int			ft_str_contains(const char *src, const char *search, size_t starting_search);
char		**ft_memcpy_array(char **src, size_t start);
int			ft_str_starts_with(const char *src, const char *value);
void		ft_replace_whitespace(char *line, char value);
char		ft_get_last_char_iw(char *line);
char		ft_get_first_char_iw(char *line);

char		**trim_command_list(char **command_list);
void		error_msg(char *string);
t_message	ft_init_messages(void);

/* *****************************************************/
/* ********************* DEBUG *************************/
/* *****************************************************/

void		ft_display_commands_list(t_commands *commands);
void		ft_display_env_map(t_env_map *env_map);
void		ft_display_env_array(char **env_array);
void		ft_display_tokens(t_tokens *tokens);
#endif
