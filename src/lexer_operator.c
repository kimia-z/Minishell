#include "lexer.h"

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

void	lexer_collect_operators(t_lexer *lexer, char *value, t_tokenlist *tokenlist)
{
	t_token	*token;
	int	op_type;

	if (ft_isspace(*value))
		return ;
	op_type = get_operator_type(value);
	if (op_type == TOKEN_OP_REDIRECTION_APPEND)
	{
		value = malloc(3);
		if (!value)
			return ;
		//strncpy would null terminated the dest
		strncpy(value, lexer->input + lexer->position, 2);
		value[2] = '\0';
		lexer->position += 2;
	}
	else
	{
		value = malloc(2);
		if (!value)
			return ;
		value[0] = lexer->input[lexer->position++];
		value[1] = '\0';
	}
	if (!*value)
		return ;
	token = token_create(op_type, value);
	tokenlist_add(tokenlist, token);
	free(value);
}