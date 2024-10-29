#include "lexer.h"

static bool is_word_token(char c)
{
	return (c != '\0' && (ft_isalpha(c) || c == '_' || c == '-'));
	
}

static bool	is_operator_token(char c)
{
	return (c != '\0' && !ft_isalnum(c));
}

static bool	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}


static int	get_num_pipes(t_tokenlist *tokens)
{

	int count;
	t_token *temp;

	temp = tokens->head;
	count = 0;
	while (temp != NULL)
	{
		if (temp->type == TOKEN_OP_PIPE)
			count++;
		temp = temp->next;
	}
	return (count);
}
/* main lexing logic - probably temporary function */
void	lexer_process_input(t_lexer *lexer, t_tokenlist *tokenlist)
{
	char current_char;
	bool is_op;
	int pos;
	pos = 1;

	while (lexer->position < lexer->length)
	{
		lexer_skip_whitespace(lexer);
		current_char = lexer->input[lexer->position];
		is_op = false;
		if (is_word_token(current_char) == true)
		{
			lexer_collect_token(lexer, tokenlist, is_op, pos);
			pos++;
		}
		else if (is_operator_token(current_char))
		{
			is_op = true;
			lexer_collect_token(lexer, tokenlist, is_op, pos);
			pos++;
		}
		else if (is_quotes(current_char))
		{
			is_op = false;
			lexer_collect_quotes(lexer, &current_char, tokenlist, is_op, pos);
			pos++;
		}
		lexer->position++;
	}
	lexer->num_pipes = get_num_pipes(tokenlist);
}


