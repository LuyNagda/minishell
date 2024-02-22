/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:45:39 by jbadaire          #+#    #+#             */
/*   Updated: 2024/02/22 16:25:19 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "boolean.h"
# include <stddef.h>

typedef enum e_token
{
	WORD = 1,
	_SPACE = 2,
	PIPE = 3,
	REDIRECT_IN = 4,
	REDIRECT_IN_DOUBLE = 5,
	REDIRECT_OUT = 6,
	REDIRECT_OUT_DOUBLE = 7,
	DOUBLE_QUOTE = 8,
	SIMPLE_QUOTE = 9,
	QUOTED = 10,
	ENV_VALUE = 12,
	INTERO = 11
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
}				t_parsing_cmd;

typedef struct s_commands
{
	char				*raw_command;
	char				**arguments;
	int					*args_quoted;
	char				*path;
	size_t				position;
	size_t				arguments_amount;
	t_boolean			has_already_executed;
	t_boolean			error_during_creation;
	int					is_builtin;
	int					input_fd;
	char				*infile;
	int					output_fd;
	char				*outfile;
	struct s_commands	*next_node;
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
	char		*semicolon_detected;
	char		*whitepipe_error;
	char		*other_input_error;

}				t_message;

typedef struct s_pipex
{
	int		index;
	int		status;
	char	*status_string;
	int		*pid;
	int		c_pipe[2];
	int		o_pipe[2];
	char	**envp;
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
	int				is_builtin;
	char			**envp;
}					t_minishell;

/* *****************************************************/
/* ******************** BUILTIN ************************/
/* *****************************************************/

void				ft_dispatch_builtin(t_minishell *shell,
						t_commands *command);
void				exec_export(t_minishell *shell, t_commands *command);
void				exec_unset(t_minishell *shell, t_commands *command);
void				exec_echo(t_minishell *shell, t_commands *command);
void				exec_pwd(t_minishell *shell);
void				exec_cd(t_minishell *shell, t_commands *command);
void				exec_env(t_minishell *shell);
void				exec_exit(t_minishell *shell, t_commands *command);
int					get_pwd(t_minishell *shell);

/* *****************************************************/
/* ********************* EXEC **************************/
/* *****************************************************/

void				ft_dispatch_command(t_minishell *shell);
void				exec_cmd(t_minishell *shell, t_commands *command);
int					is_builtins(t_commands *command);
char				**convert_path_to_array(t_env_map *env_map);
char				*find_command(t_env_map *map, char *command);
void				free_and_exit(t_minishell *shell, t_pipex *pipex, int code);
void				here_doc(t_minishell *shell,
						t_commands *command, t_pipex *pipex);
void				normal_redirections(t_minishell *shell,
						t_commands *command, t_pipex *pipex);
int					here_doc_execution(t_minishell *shell,
						t_commands *tmp, int i);

/* *****************************************************/
/* ********************** ENV **************************/
/* *****************************************************/

void				env_map_init(t_minishell *shell);
t_env_map			*ft_create_env_node(char *k, char *v,
						int has_equals, int is_system);
t_env_map			*env_map_add_back(t_env_map **env_map,
						t_env_map *new_node, int is_immutable);
t_env_map			*env_map_remove_back(t_env_map *env_map);
t_env_map			*env_map_remove_from_key(t_env_map *env_map, char *key);
t_env_map			*env_map_replace(t_env_map *env_map,
						char *key, char *value);
t_env_map			*env_map_find_node(t_env_map *env_map, char *key);
t_env_map			*env_array_to_map(t_minishell *shell,
						t_env_map **env_map, char **env);
t_env_map			*env_map_replace_or_add(t_env_map *env_map,
						char *key, char *value);
char				**env_map_to_array(t_env_map *env_map);
char				*env_map_get_key(t_env_map *env_map, size_t node_pos);
void				env_map_flush(t_env_map *env_map);
size_t				env_map_get_size(t_env_map *env_map);

/* *****************************************************/
/* ******************** COMMANDS ***********************/
/* *****************************************************/

t_commands			*build_command_loop(t_minishell *shell, char **args, size_t arg_index);
size_t				ft_get_numbers_of_commands(t_commands *commands_list);
t_commands			*ft_get_command_from_pos(t_commands *command_list,
						size_t command_node_pos);
t_commands			*ft_add_command(t_minishell *shell, t_commands *new_node);
size_t				ft_get_arguments_amount(t_commands *command);
t_commands			*ft_command_new_node(t_env_map *map, char **args);
t_commands			*ft_create_command_node(char *cmd);
void				ft_flush_command_list(t_commands *list);
void				*ft_populate_command_list(t_minishell *shell);
int					*ft_fill_args_quotes(char **args);

/* *****************************************************/
/* ******************** PARSING ************************/
/* *****************************************************/

t_parsing_result	pre_parsing(t_minishell *shell);
t_parsing_result	on_parse(t_minishell *shell);
t_parsing_result	post_parsing(t_minishell *shell);
int					has_redirection(t_commands *command, char character);
void				redirection_parsing(t_minishell *shell,
						t_commands *commands, char *character, t_pipex *pipex);
void				heredoc_parsing(t_minishell *shell,
						t_commands *command, char *here_doc, t_pipex *pipex);
int					has_heredoc(t_commands *command, char *here_doc);
int					count_redirection(t_commands *command, char *character);
void				remove_file_from_command(t_commands *command,
						char *character, int i);
int					has_multiple_redirection(t_commands *command,
						char *character);
char				**get_export_values(t_commands *command,
						int *i, int *has_equal);
void				add_back_command_path(t_minishell *shell,
						t_commands *command);
int					ft_string_in_quotes(char *str);
char				*expand_line(char *str, t_env_map *map, int must_expanded);

/* *****************************************************/
/* ******************** TOKENS *************************/
/* *****************************************************/

void				tokenize_input(t_minishell *shell);
void				ft_split_to_tokens(t_minishell *shell, size_t cur_pos, int tmp);
t_tokens			*ft_create_token(char *token, t_token_type token_type);
void				ft_add_back_token(t_tokens **tokens_list, t_tokens *token);
void				add_token_after(t_tokens **tokens,
						t_tokens *new_token, t_tokens *after);
void				ft_delete_token(t_tokens **head, t_tokens *token);
void				ft_flush_tokens(t_tokens *tokens);
size_t				get_current_token_pos(t_tokens *tokens);
char				*rebuild_string_from_token(t_minishell *shell);
void				append_token(t_tokens *appended, t_tokens *to_append);
void				ft_concat_quoted_pipes(t_minishell *shell, char *final_str);
size_t				ft_tokens_len(t_tokens *tokens);
size_t				ft_get_tokens_amount(t_tokens *tokens);
size_t				ft_get_tokens_type_amount(t_tokens *tokens,
						t_token_type tokenType);
long long			ft_next_token_pos(t_tokens *tok,
						t_token_type type, long long start);
size_t				get_index_from_token(t_minishell *shell, size_t token_pos);
void				ft_free_token(t_tokens *token);

/* *****************************************************/
/* ********************* UTILS *************************/
/* *****************************************************/

int					ft_quote_is_closed(const char *line);
int					ft_index_is_in_quote(const char *line,
						size_t pos, char quote);
int					ft_index_is_in_quotes(const char *line, size_t pos);
int					ft_str_equals(const char *str1, const char *str2);
int					ft_str_index_of(const char *src, const char *search,
						size_t *start_at, size_t starting_search);
int					ft_str_contains(const char *src, const char *search,
						size_t starting_search);
char				**ft_memcpy_array(char **src, char **dest, size_t start);
int					ft_str_starts_with(const char *src, const char *value);
void				ft_replace_whitespace(char *line, char value);
char				ft_get_last_char_iw(char *line);
char				ft_get_first_char_iw(char *line);
void				error_msg(char *string);
char				*build_str_from_array(char **array);
t_message			ft_init_messages(void);
t_env_map			*duplicate_list(t_env_map *head);
t_env_map			*merge_sort(t_env_map *head);
void				free_duplicate_env(t_env_map *head);

/* *****************************************************/
/* ******************** SIGNALS ************************/
/* *****************************************************/
t_minishell			*get_minishell(t_minishell *minishell);
void				hook_exit_signal(void);
void				hook_signal_on_start(void);
void				hook_heredoc_signal(void);
void				handle_ignored_signal(void);

/* *****************************************************/
/* ********************* DEBUG *************************/
/* *****************************************************/

void				ft_display_commands_list(t_commands *commands);
void				ft_display_env_map(t_env_map *env_map);
void				ft_display_env_array(char **env_array);
void				ft_display_tokens(t_tokens *tokens);

/* *****************************************************/
/* ******************* GLOBAL VAR **********************/
/* *****************************************************/
extern int			g_signal_state;

#endif
