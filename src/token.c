#include "lexer.h"

/* Create a new token of the given type and value */
t_token	*token_create(token_type type, char *value)
{
	t_token	*token;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
		return (NULL);
	token->next = NULL;
	//printf("token created. type: %d, value: %s.\n", token->type, token->value);
	return (token);
}

/*Im not sure about the name of this function change it if
it is not clear :* */
void	create_word_token(size_t start, size_t len, t_lexer *lexer, t_tokenlist *tokenlist)
{
	t_token	*token;
	char	*word;

	word = strndup(lexer->input + start, len);
	if (!word)
		return ; // also print sth
	token = token_create(TOKEN_WORD, word);
	lexer_skip_whitespace(lexer);
	tokenlist_add(tokenlist, token);
	free(word);
}

void	token_free(t_token *token)
{
	if (!token)
		return;
	free(token->value);
	free(token);
}
