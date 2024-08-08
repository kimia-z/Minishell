#include "lexer.h"

void lexer_collect_token(t_lexer *lexer, t_tokenlist *tokenlist, bool is_op)
{
	size_t	start;
	size_t	len;
	char	*word;
	t_token	*token;
	int		op_type;

	lexer_skip_whitespace(lexer);
	start = lexer->position;
	while (lexer->position < lexer->length && !ft_isspace(lexer->input[lexer->position]))
		lexer->position++;
	len = lexer->position - start;
	word = strndup(lexer->input + start, len);
	if (is_op == true)
	{
		op_type = get_operator_type(word);
		token = token_create(op_type, word);
	}
	else
		token = token_create(TOKEN_WORD, word);	
	tokenlist_add(tokenlist, token);
	free(word);
}

token_type	get_operator_type(char *value)
{
	if (*value == '>' && *(value + 1) == '>')
		return (TOKEN_OP_REDIRECTION_APPEND);
	else if (*value == '<')
		return (TOKEN_OP_REDIRECTION_IN);
	else if (*value == '>')
		return (TOKEN_OP_REDIRECTION_OUT);
	else if (*value == '|')
		return (TOKEN_OP_PIPE);
	else
		return (TOKEN_UNKNOWN);
}
