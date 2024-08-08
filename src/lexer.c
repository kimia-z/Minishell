#include "lexer.h"


/* Initialize lexer with the given input */
t_lexer	*lexer_init(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = ft_strdup(input);
	if (!lexer->input)
		return (NULL);
	lexer->tokens = NULL;
	lexer->position = 0;
	lexer->length = ft_strlen(input);
	lexer->start = 0;
	return (lexer);
}

void	lexer_free(t_lexer *lexer)
{
	if (!lexer)
		return ;
	free(lexer->input);
	free(lexer);
}

void	lexer_process_input(t_lexer *lexer, t_tokenlist *tokenlist)
{
	char current_char;
	bool is_op;

	while (lexer->position < lexer->length)
	{
		lexer_skip_whitespace(lexer);
		current_char = lexer->input[lexer->position];
		is_op = false;
		if (is_word_token(current_char) == true)
			lexer_collect_token(lexer, tokenlist, is_op);
		else if (is_operator_token(current_char))
		{
			is_op = true;
			lexer_collect_token(lexer, tokenlist, is_op);
		}
		else if (is_quotes(current_char))
		{
			is_op = false;
			lexer_collect_quotes(lexer, &current_char, tokenlist, is_op);
		}
		lexer->position++;
	}
}

/*
// lexer should return a list(or any other data structure) of tokens
// receives a structs thats gonna hold other info about the shell (the big general struct) and a character pointer that's
// a string (commandline input)
t_list lexer(t_info info, char *input)
{
	t_list *token_list;
	token_list = tokenlist_init();
	while(*input)
	{
		*input = lexer_skip_leading_whitespce();
		if (!*input)
			break ;
		if (is_metacharacter(*input))
			create_token();
		else (isaplpha(*input))
			create_token();
		else
			do error;
		add tokens to token list;
		check for error;
		check for syntactical error;
		
	}
	return tokenlist;
}
*/