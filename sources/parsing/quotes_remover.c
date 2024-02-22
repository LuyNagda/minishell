#include <stdio.h>
#include "minishell.h"
#include "string_utils.h"

static void	remove_char_string(char *str, char d)
{
	size_t	index;
	size_t	final_index;

	index = 0;
	final_index = 0;
	if (str == NULL)
		return ;
	while (str[index])
	{
		if (str[index] != d)
			str[final_index++] = str[index];
		index++;
	}
	str[final_index] = '\0';
}

static void	replace_quotes_loop(t_commands *commands, size_t args_index, \
	size_t *str_index, int *quote_type)
{
	char	c;

	while (commands->arguments[args_index][(*str_index)])
	{
		c = commands->arguments[args_index][(*str_index)];
		if (c == '\'')
		{
			if (*quote_type == 0)
				*quote_type = 1;
			else if (*quote_type == 1)
				*quote_type = 0;
			if (*quote_type == 1 || *quote_type == 0)
				commands->arguments[args_index][(*str_index)] = '\a';
		}
		else if (c == '\"')
		{
			if (*quote_type == 0)
				*quote_type = 2;
			else if (*quote_type == 2)
				*quote_type = 0;
			if (*quote_type == 2 || *quote_type == 0)
				commands->arguments[args_index][(*str_index)] = '\a';
		}
		(*str_index)++;
	}
}

static void	remove_quotes_loop(t_commands *commands)
{
	size_t	args_index;
	size_t	str_index;
	int		quote_type;

	args_index = 0;
	while (commands->arguments[args_index])
	{
		if (!ft_str_contains(commands->arguments[args_index], "'", 0) && \
			!ft_str_contains(commands->arguments[args_index], "\"", 0))
		{
			args_index++;
			continue ;
		}
		str_index = 0;
		quote_type = 0;
		replace_quotes_loop(commands, args_index, &str_index, &quote_type);
		remove_char_string(commands->arguments[args_index], '\a');
		args_index++;
	}
}

t_parsing_result	remove_quotes(t_minishell *shell)
{
	t_commands	*commands;

	commands = shell->commands;
	while (commands)
	{
		remove_quotes_loop(commands);
		commands = commands->next_node;
	}
	return (SUCCESS);
}
