#include "lexer.h"

/* Initialize a new token list */
t_tokenlist	*tokenlist_init(void)
{
	t_tokenlist	*list;
	list = malloc(sizeof(t_tokenlist));
	if (!list)
		return (NULL);
	ft_bzero(list, sizeof(t_tokenlist));
	list->token_count = 0;
	list->head = NULL;
	return (list);
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

void tokenlist_print(t_token *head)
{
	int i = 0;
	t_token *current = head;
	while (current != NULL)
	{
		printf("%d  - ", i);

		printf("Token Type: %d, Token Value: %s, tok pos: %d\n", current->type, current->value, current->position);
		current = current->next;
		i++;
	}
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