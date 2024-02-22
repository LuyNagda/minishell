#include <libft.h>

#include "minishell.h"
#include "put_utils.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>

static void	treat_spaced_values(t_minishell *shell,
	t_tokens *current, char *value)
{
	char		**split;
	char		*str;
	t_tokens	*new;
	size_t		split_size;

	if (!ft_str_contains(value, " ", 0))
		return ;
	split = ft_split(value, ' ');
	if (split == NULL)
		return ;
	split_size = ft_str_tab_len(split) -1;
	while (split[split_size] != NULL && split_size > 0)
	{
		str = ft_strdup(split[split_size]);
		if (str == NULL)
			continue ;
		new = ft_create_token(str, ENV_VALUE);
		if (new == NULL)
			continue ;
		add_token_after(&shell->parsing_cmd.tokens, new, current);
		add_space_token(shell, new);
		split_size--;
	}
	ft_free_split(split);
}

static int	contains_valid_key(t_minishell *shell, t_tokens *token)
{
	t_tokens	*previous;
	size_t		nb_dollars;
	size_t		token_pos;
	char		*rebuilded_string;

	if (token->type != WORD && token->type != QUOTED && token->type != INTERO)
		return (_false);
	nb_dollars = 0;
	previous = token->previous;
	while (previous && previous->value
		&& previous->value[0] == '$' && ++nb_dollars)
		previous = previous->previous;
	if (nb_dollars != 1)
		return (_false);
	rebuilded_string = rebuild_string_from_token(shell);
	if (rebuilded_string == NULL)
		return (_false);
	token_pos = get_current_token_pos(token);
	if (!variable_in_quotes(rebuilded_string, \
		get_index_from_token(shell, token_pos)))
		return (free(rebuilded_string), _false);
	return (free(rebuilded_string), _true);
}

static t_boolean	process_previous_token(t_tokens *tmp, char *str)
{
	char	**split;
	char	*dup;

	free(tmp->previous->value);
	tmp->previous->value = NULL;
	split = ft_split(str, ' ');
	if (split == NULL)
		return (_true);
	dup = ft_strdup(split[0]);
	if (dup == NULL)
		return (_true);
	tmp->previous->value = dup;
	tmp->previous->type = ENV_VALUE;
	ft_free_split(split);
	return (_false);
}

static t_boolean	process_space(t_minishell *shell, t_tokens *tmp, char *str)
{
	char	*space;

	if (tmp->previous)
		if (process_previous_token(tmp, str))
			return (_true);
	free(tmp->value);
	space = ft_strdup(" ");
	if (space == NULL)
		return (_true);
	tmp->value = space;
	tmp->type = _SPACE;
	treat_spaced_values(shell, tmp, str);
	free(str);
	return (_false);
}

static void	process_expand(t_minishell *shell, t_tokens *tmp, char *value)
{
	char	*str;

	if (value == NULL)
		return ;
	str = ft_strdup(value);
	if (str == NULL)
		return ;
	if (ft_str_contains(str, " ", 0))
		if (process_space(shell, tmp, str))
			return ;
	delete_prev_token(shell, tmp);
	free(tmp->value);
	tmp->value = str;
	tmp->type = ENV_VALUE;
}

t_boolean	expand_status(t_minishell *shell, char **value)
{
	t_env_map	*env_finded;

	env_finded = env_map_find_node(shell->env_map, "?");
	if (!env_finded)
		*value = ft_strdup("0");
	else
		*value = ft_strdup(env_finded->value);
	if (!*value)
		return (_true);
	return (_false);
}

t_boolean	expand_normal(t_minishell *shell, t_tokens *tokens, char **value)
{
	char		*trim;
	t_env_map	*env_finded;

	env_finded = env_map_find_node(shell->env_map, tokens->value);
	if (env_finded == NULL)
	{
		*value = ft_strdup("");
		if (!*value)
			return (_true);
	}
	else
	{
		*value = ft_strdup(env_finded->value);
		if (!*value)
			return (_true);
		if (tokens->type != QUOTED)
		{
			trim = ft_strtrim(*value, " ");
			free(*value);
			*value = trim;
		}
	}
	return (_false);
}

void	free_value(char **value)
{
	if (*value)
	{
		free(*value);
		*value = NULL;
	}
}

void	treat_variable_keys(t_minishell *shell, char *value)
{
	t_tokens	*tokens;

	tokens = shell->parsing_cmd.tokens;
	while (tokens)
	{
		if (!contains_valid_key(shell, tokens))
		{
			tokens = tokens->next;
			continue ;
		}
		if (ft_str_starts_with(tokens->value, "?"))
		{
			if (expand_status(shell, &value))
				return ;
		}
		else
		{
			if (expand_normal(shell, tokens, &value))
				return ;
		}
		process_expand(shell, tokens, value);
		free_value(&value);
		tokens = tokens->next;
	}
}
