#include "lexer.h"
#include "parser.h"
#include <readline/readline.h>

char	*get_line()
{
	char	*input;

	input = readline("Minishell: ");
	if (!input)
	{
		return (NULL);
	}
	return (input);
}

int main()
{
	// t_lexer 	*lexer;
	// t_tokenlist	*tokenlist;
	char		*input;

	input = get_line();
	printf("input is:%s\n", input);
	free(input);
	// lexer = lexer_init(input);
	// printf("input: %s\n", lexer->input);
	// tokenlist = tokenlist_init();
	// lexer_process_input(lexer, tokenlist);
	// lexer_free(lexer);
	// tokenlist_print(tokenlist->head);
	// parser(tokenlist);
	// tokenlist_free(tokenlist);
	
	return (0);
}