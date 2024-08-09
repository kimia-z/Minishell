#include "grammar.h"
#include "lexer.h"

/***** it should be a loop through each token and call pipe_seq function ****/


/* check the grammar for cmd_word 
	for the filename, here_end, cmd_name
	same function as this one*/
t_cmd_word *ft_cmd_word(t_token *token)
{
	t_cmd_word	*cmd_word;

	if (token->type == TOKEN_WORD)
	{
		cmd_word = malloc(sizeof(t_cmd_word));
		if (!cmd_word)
		{
			write_stderr("");
		}
		cmd_word->word = strndup(token->value, token->size);
		if (!cmd_word->word)
		{
			write_stderr("");
		}
		return (cmd_word);
	}
	return (NULL);
}

t_simple_command *ft_simple_command(t_token *token)
{
	t_simple_command	*simple_cmd;
	t_cmd_prefix		*cmd_prefix;
	t_cmd_suffix		*cmd_suffix;
	t_cmd_word			*cmd_word;
	t_cmd_name			*cmd_name;

	simple_cmd = malloc(sizeof(t_simple_command));
	if (!simple_cmd)
	{
		write_stderr("");
	}
	if (cmd_prefix = ft_cmd_prefix(token->value))
	{
		token = token->next;
		if (cmd_word = ft_cmd_word(token))
		{
			token = token->next;
			if (cmd_suffix = ft_cmd_suffix(token->value))
			{
				token = token->next;
				return (simple_cmd);
			}
			return (simple_cmd);
		}
		return (simple_cmd);
	}
	else if (cmd_name = ft_cmd_name(token))
	{
		token = token->next;
		if (cmd_suffix = ft_cmd_suffix(token->value))
		{
			token = token->next;
			return (simple_cmd);
		}
	}
	else
		return (NULL);
}

/* check the grammar for pipeline*/
t_pipe_seq *ft_pipe_seq(t_tokenlist *tokenlist)
{
	t_pipe_seq			*pipe_seq;
	t_simple_command	*simple_cmd;
	
	pipe_seq = malloc(sizeof(t_pipe_seq));
	if (!pipe_seq)
	{
		write_stderr("");
	}
	while (simple_cmd = ft_simple_command(tokenlist->head))
	{
		// a function that will push new simple cmd(pipe seq struct)
		//to simple cmd struct(pushes a new element into a linked list)
		ft_lst_push(simple_cmd, pipe_seq->simple_cmd);
		if (tokenlist->head->type == TOKEN_OP_PIPE)
			tokenlist->head == tokenlist->head->next;
	}
	if (pipe_seq->simple_cmd)
		return (pipe_seq);
	free(pipe_seq);
	return (NULL);
}
