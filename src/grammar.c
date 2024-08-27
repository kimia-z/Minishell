#include "lexer.h"

/***** it should be a loop through each token and call pipe_seq function ****/


/* check the grammar for cmd_word 
	for the filename, here_end, cmd_name
	same function as this one*/
/*
bool	is_word(t_token *token)
{
	if (token->type == TOKEN_WORD)
	{
		return (true);
	}
	return (false);
}

bool	is_io_file(t_token *token)
{
	if (token->value == TOKEN_OP_REDIRECTION_IN || token->value == TOKEN_OP_REDIRECTION_OUT || token->value == TOKEN_OP_REDIRECTION_APPEND)
	{
		token = token->next;
		if (is_word(token))
		{
			return (true);
		}
	}
	return (false);
}

bool	is_io_redirect(t_token *token)
{
	if (is_io_file(token))
	{
		token = token->next;
		return (true);
	}
	else if (is_io_here(token))
	{
		token = token->next;
		return (true);
	}
	return (false);
}

bool	is_cmd_prefix(t_token *token)
{
	char	*io_redirect;

	while (io_redirect = is_io_redirect(token))
	{
		continue;
	}
	if (io_redirect)
		return (true);
	return (false);
}

bool	is_simple_command(t_token *token)
{
	if (is_cmd_prefix(token->value))
	{
		token = token->next;
		if (is_word(token))
		{
			token = token->next;
			if (is_cmd_suffix(token->value))
			{
				token = token->next;
				return (true);
			}
			return (true);
		}
		return (true);
	}
	else if (is_word(token))
	{
		token = token->next;
		if (is_cmd_suffix(token->value))
		{
			token = token->next;
			return (true);
		}
		return (true);
	}
	else
		return (false);
}

bool	is_pipe_seq(t_tokenlist *tokenlist)
{
	bool	simple_cmd;
	
	while (simple_cmd = is_simple_command(tokenlist->head))
	{
		if (tokenlist->head->type == TOKEN_OP_PIPE)
			tokenlist->head == tokenlist->head->next;
	}
	if (simple_cmd)
		return (true);
	return (false);
}
*/