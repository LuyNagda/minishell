/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:45:39 by jbadaire          #+#    #+#             */
/*   Updated: 2024/01/05 12:32:54 by lunagda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../dependencies/libft/.includes/boolean.h"
# include <stddef.h>

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
	SIMPLE_QUOTE = 9
}	t_token_type;

typedef struct s_tokens
{
	t_token_type	type;
	char			value;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_commands
{
	t_tokens	*tokens;
	size_t		last_end;
	long long	next_start;
	char		*latest_command;
}				t_commands;

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

typedef struct s_minishell
{
	t_boolean	is_running;
	t_env_map	*env_map;
	t_message	messages;

	char		*sended_line;
	t_commands	commands;
}				t_minishell;

typedef struct s_builtin
{
	char				*name;
	char				*args;
	int					(*ptr_func)(t_minishell *minishell);
	struct s_builtin	*next_builtin;
}			t_builtin;

/* *****************************************************/
/* ********************* EXEC **************************/
/* *****************************************************/

void		ft_dispatch_commands(t_minishell *shell);
void		exec_simple_pipex(t_minishell *shell, char *line);
char		**convert_path_to_array(t_env_map *env_map);
char		*find_command(char *command, char **path_array);
void		exec_simple_cmd(t_minishell *minishell, char *cmd);

/* *****************************************************/
/* ********************** ENV **************************/
/* *****************************************************/

t_env_map	*env_map_init(char **env_array);
t_env_map	*ft_create_env_node(char *k, char *v, int has_equals, int is_system);
t_env_map	*env_map_add_back(t_env_map **env_map, t_env_map *new_node, int is_immutable);
t_env_map	*env_map_remove_back(t_env_map *env_map);
t_env_map	*env_map_remove_from_key(t_env_map *env_map, char *key);
t_env_map	*env_map_replace(t_env_map *env_map, char *key, char *value);
t_env_map	*env_map_find_node(t_env_map *env_map, char *key);
t_env_map	*env_array_to_map(t_env_map **env_map, char **env);

char		**env_map_to_array(t_env_map *env_map);
char		*env_map_get_key(t_env_map *env_map, size_t node_pos);
void		env_map_flush(t_env_map *env_map);

size_t		env_map_get_size(t_env_map *env_map);

/* *****************************************************/
/* ******************** PARSING ************************/
/* *****************************************************/

void		parse_input(t_minishell *shell);
char		*ft_concat_tokens(t_minishell *shell, t_boolean reset_values);
void		ft_concat_quoted_pipes(t_minishell *shell, char *final_str);
void		ft_post_command(t_minishell *shell);
/* *****************************************************/
/* ******************** TOKENS *************************/
/* *****************************************************/

t_tokens	*ft_create_token(char token, t_token_type token_type);
void		ft_add_black_token(t_tokens **tokens_list, t_tokens *token);
void		ft_flush_tokens(t_tokens *tokens);
void		ft_default_cmd_struct(t_minishell *shell, t_boolean reset_tokens);

char		*ft_concat_same_tokens_type(t_tokens *tokens, t_token_type token_type);
char		*ft_concat_tokens_util_type(t_tokens *tokens, size_t start_pos, t_token_type type);
char		*ft_concat_tokens_util_end(t_tokens *tokens, size_t start_pos);

size_t		ft_get_tokens_amount(t_tokens *tokens);
size_t		ft_get_tokens_type_amount(t_tokens *tokens, t_token_type tokenType);
long long	ft_next_token_pos(t_tokens *tok, t_token_type type, long long start);
size_t		ft_total_length(t_tokens *tokens);

/* *****************************************************/
/* ********************* UTILS *************************/
/* *****************************************************/

int			ft_has_valid_history(char *line);

int			ft_is_quote(char c, char quote);
int			ft_count_quotes(char *line, char character);
int			ft_quote_is_closed(const char *line);
int			ft_index_is_in_quote(const char *line, size_t pos, char quote);
int			ft_index_is_in_quotes(const char *line, size_t pos);
int			ft_quote_is_closed_range(const char *line, size_t start, size_t end);
int			ft_str_equals(const char *str1, const char *str2);
int	ft_str_contains(const char *src, const char *search, size_t *start_at, size_t starting_search);
int			ft_str_starts_with(const char *src, const char *value);
void		ft_replace_whitespace(char *line, char value);
char	*ft_replace_all(char *line, const char *replaced, const char *replacer);
size_t		ft_find_first(const char *str, char charset);
size_t		ft_find_first_charset(const char *haystack, const char *needle);
char		ft_get_last_char_iw(char *line);
char		ft_get_first_char_iw(char *line);
int			ft_str_only_whitespace(const char *src);

t_message	ft_init_messages(void);

/* *****************************************************/
/* ********************* DEBUG *************************/
/* *****************************************************/

void		ft_display_env_map(t_env_map *env_map);
void		ft_display_env_array(char **env_array);
void		ft_display_tokens(t_tokens *tokens);
#endif
