#include "parser.h"

bool is_pipeline(t_tokenlist *tokenlist)
{
	t_token	*temp;

	temp = tokenlist->head;
	while (temp != NULL)
	{
		if (temp->type == TOKEN_OP_PIPE)
			return (true);
		temp = temp->next;
	}
	return (false);
}
bool is_redirection(t_tokenlist *tokenlist)
{
	t_token	*temp;

	temp = tokenlist->head;
	while (temp != NULL)
	{
		if (temp->type == TOKEN_OP_REDIRECTION_APPEND || temp->type == TOKEN_OP_REDIRECTION_IN || temp->type == TOKEN_OP_REDIRECTION_OUT)
			return (true);
		temp = temp->next;
	}
	return (false);
}

bool is_command(t_tokenlist *tokenlist)
{
	t_token	*temp;

	temp = tokenlist->head;
	while (temp != NULL)
	{
		if (temp->type == TOKEN_WORD)
			return (true);
		temp = temp->next;
	}
	return (false);
}



// t_node *parse_arguments(t_tokenlist *tokenlist)
// {

// }

// parse_command()
// {}