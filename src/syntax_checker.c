#include "parser.h"

static bool is_invalid_position(size_t position, size_t token_count)
{
	return (position == 0 || position == token_count - 1);
}

static int is_operator(token_type type)
{
	return (type == TOKEN_OP_PIPE || type == TOKEN_OP_REDIRECTION_OUT || type == TOKEN_OP_REDIRECTION_IN || type == TOKEN_OP_REDIRECTION_APPEND);
}

static int operator_checker(token_type type, size_t position, size_t token_count, token_type left_op)
{
	if (is_operator(type) && (is_invalid_position(position, token_count) || is_operator(left_op)))
		return (1);
	return 0;
}

/* preliminary synax checker - needs to be updated with all the cases */
int syntax_checker(t_tokenlist *tokenlist)
{
	t_token		*temp;
	size_t		i;
	token_type	left_op;

	i = 0;
	left_op = TOKEN_WORD;
	temp = tokenlist->head;
	while (temp != NULL)
	{
		if (is_operator(temp->type))
		{
			if (operator_checker(temp->type, i, tokenlist->token_count, left_op) == 1)
			{
				write_stderr("Syntax not correct.");
				return (1);
			}
		}
		else if (temp->type == TOKEN_UNKNOWN)
		{
			write_stderr("Syntax not correct, unknown operator.");
			return (1);
		}
		i++;
		left_op = temp->type;
		temp = temp->next;
	}
	return 0;
}