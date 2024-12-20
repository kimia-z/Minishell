#include "lexer.h"
#include "parser.h"
#include "minishell.h"

static bool	is_quote_closed(t_lexer *lexer, char *value)
{
	if (ft_strchr(lexer->input + lexer->position + 1, *value))
		return (true);
	return (false);
}

/* Calculates the length of the quoted section */
static size_t	len_quotes(char *value)
{
	size_t	i;

	i = 1;
	while (value[i] && value[i] != *value)
		i++;
	return (i - 1);
}

void	*lexer_collect_quotes(t_lexer *lexer, char *value, t_tokenlist *tokenlist, bool is_op)
{
	size_t len;

	if (!is_quote_closed(lexer, value))
	{
		//error unclosed
		return NULL;
	}
	len = len_quotes(value);
	lexer->position++;
	if (*value == '\'' || *value == '"')
	{
		if (!lexer_collect_token(lexer, tokenlist, is_op))
			return (NULL);
		lexer->position += len + 1;
	}
	return ((char *)1); // indication of success
}
