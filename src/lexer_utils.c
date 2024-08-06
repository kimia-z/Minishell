#include "lexer.h"

/* Checks if a character is a metacharacter */
bool is_metacharacter(char c)
{
    if (c == '\0')
		return (false);
    if (ft_strchr("|<>; \t\n", c) == NULL)
		return (false);
	return (true);
}

/* probably not gonna need it(for leading whitespace) */
/* updates the struct */
void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->position < lexer->length && ft_isspace(lexer->input[lexer->position]))
		lexer->position++;
}


bool	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}
/* check if the quotes are closed */
bool	is_quote_closed(t_lexer *lexer, char *value)
{
	if (ft_strchr(lexer->input + lexer->position + 1, *value))
		return (true);
	return (false);
}

/* Calculates the length of the quoted section */
size_t	len_quotes(char *value)
{
	size_t	i;

	i = 1;
	while (value[i] && value[i] != *value)
		i++;
	return (i - 1);
}

