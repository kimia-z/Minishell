#include "lexer.h"

/* Create a new token of the given type and value */
t_token	*token_create(token_type type, char *value)
{
	t_token	*token;
	token = malloc(sizeof(t_token));
	if (!token)
	{
		//lexer_free(lexer);
		//tokenlist_free(tokenlist);
		error_msg("");
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	//printf("token created. type: %d, value: %s.\n", token->type, token->value);
	return (token);
}

/* Add a token to the token list */
void	tokenlist_add(t_tokenlist *list, t_token *token)
{
	t_token	*current;
	if (!list->head)
	{
		list->head = token;
	}
	else
	{
		current = list->head;
		while (current->next)
			current = current->next;
		current->next = token;
	}
	list->token_count++;
}

void	token_free(t_token *token)
{
	if (!token)
		return;
	if (token->value)
		free(token->value);
	free(token);
}

/* Initialize a new token list */
t_tokenlist	*tokenlist_init(void)
{
	t_tokenlist	*list;
	list = malloc(sizeof(t_tokenlist));
	if (!list)
		return (NULL);
	list->token_count = 0;
	list->head = NULL;
	return (list);
}

/* Free the memory allocated for the token list and its tokens */
void	tokenlist_free(t_tokenlist *list)
{
	t_token	*next;
	t_token	*current;

	if (!list)
		return;
	current = list->head;
	while (current)
	{
		next = current->next;
		token_free(current);
		current = next;
	}
	free(list);
}