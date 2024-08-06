#include "lexer.h"

void	lexer_process_input(t_lexer *lexer, t_tokenlist *tokenlist)
{
	while (lexer->position < lexer->length)
	{
		lexer_skip_whitespace(lexer);
		if (is_metacharacter(lexer->input[lexer->position]))
			lexer_collect_operators(lexer, &lexer->input[lexer->position], tokenlist);
		else if (ft_isalpha(lexer->input[lexer->position]))
			lexer_collect_word(lexer, tokenlist);
		else if (is_quotes(lexer->input[lexer->position]))
			lexer_collect_quotes(lexer, &lexer->input[lexer->position], tokenlist);
		else
		{
			lexer->position++;
			continue;
		}
	}
}


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