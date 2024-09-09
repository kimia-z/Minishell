#include "lexer.h"

/* Create a new token of the given type and value */
t_token	*token_create(token_type type, char *value)
{
	t_token	*token;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
		return (NULL);
	token->next = NULL;
	//printf("token created. type: %d, value: %s.\n", token->type, token->value);
	return (token);
}


void	token_free(t_token *token)
{
	if (!token)
		return;
	free(token->value);
	free(token);
}
