#include <libft.h>
#include "minishell.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>

void	treat_spaced_values(t_minishell *shell,
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

int	contains_valid_key(t_minishell *shell, t_tokens *token)
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

t_boolean	process_previous_token(t_tokens *tmp, char *str)
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

static void	free_value(char **value)
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
