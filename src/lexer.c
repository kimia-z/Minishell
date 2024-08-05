#include "lexer.h"

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

void lexer_collect_word(t_lexer *lexer, t_tokenlist *tokenlist)
{
	size_t	start;
	size_t	len;

	lexer_skip_whitespace(lexer);
	start = lexer->position;
	while (lexer->position < lexer->length && !is_metacharacter(lexer->input[lexer->position]))
	{
		// if (is_quote(lexer->input[lexer->position]))
		// {
		// 	ignore quotes

		// }
		lexer->position++;
	}
	len = lexer->position - start;
	create_word_token(start, len, lexer, tokenlist);
}

token_type	get_operator_type(char *value)
{
	if (*value == '>' && *(value + 1) == '>')
		return (TOKEN_OP_REDIRECTION_APPEND);
	else if (*value == '<')
		return (TOKEN_OP_REDIRECTION_IN);
	else if (*value == '>')
		return (TOKEN_OP_REDIRECTION_OUT);
	else if (*value == '|')
		return (TOKEN_OP_PIPE);
	else
		return (TOKEN_UNKNOWN);
}


void	lexer_collect_operators(t_lexer *lexer, char *value, t_tokenlist *tokenlist)
{
	t_token	*token;
	int	op_type;

	if (ft_isspace(*value))
		return ;
	op_type = get_operator_type(value);
	if (op_type == TOKEN_OP_REDIRECTION_APPEND)
	{
		value = malloc(3);
		if (!value)
			return ;
		//strncpy would null terminated the dest
		strncpy(value, lexer->input + lexer->position, 2);
		value[2] = '\0';
		lexer->position += 2;
	}
	else
	{
		value = malloc(2);
		if (!value)
			return ;
		value[0] = lexer->input[lexer->position++];
		value[1] = '\0';
	}
	if (!*value)
		return ;
	token = token_create(op_type, value);
	tokenlist_add(tokenlist, token);
	free(value);
}


void	lexer_process_input(t_lexer *lexer)
{
	t_tokenlist	*tokenlist;

	tokenlist = tokenlist_init();
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
			printf("Unknown token\n");
			lexer->position++;
			continue;
		}
	}
	print_token_list(tokenlist->head);
	tokenlist_free(tokenlist);
}

void print_token_list(t_token *head)
{
	t_token *current = head;
	while (current != NULL)
	{
		printf("Token Type: %d, Token Value: %s\n", current->type, current->value);
		current = current->next;
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