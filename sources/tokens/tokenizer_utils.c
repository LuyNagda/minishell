#include "minishell.h"
#include "char_utils.h"
#include "string_utils.h"
#include <stdlib.h>

static t_boolean	is_word(char c)
{
	return (c != '\'' && c != '\"' && c != '$' && \
		c != '|' && c != '>' && c != '<' && \
		!ft_is_whitespace(c));
}

void	ft_split_to_tokens(t_minishell *shell, size_t cur_pos, int tmp)
{
	char		*sended;
	t_tokens	*token;

	sended = shell->sended_line;
	while (sended[0])
	{
		if (!(is_word(sended[0])))
		{
			token = ft_create_token(ft_substr(sended++, 0, 1), 1);
			if (!token)
				break ;
			ft_add_back_token(&shell->parsing_cmd.tokens, token);
			continue ;
		}
		cur_pos = 0;
		while (sended[cur_pos] && is_word((sended[cur_pos])))
			cur_pos++;
		token = ft_create_token(ft_substr(sended, 0, cur_pos), 1);
		if (!token)
			break ;
		ft_add_back_token(&shell->parsing_cmd.tokens, token);
		tmp = 0;
		while (cur_pos > tmp++)
			sended++;
	}
}
