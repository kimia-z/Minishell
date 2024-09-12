#include "lexer.h"
#include "parser.h"
#include <readline/readline.h>

// char	*get_line()
// {
// 	char	*input;

// 	input = readline("Minishell: ");
// 	if (!input)
// 	{
// 		return (NULL);
// 	}
// 	return (input);
// }

int main()
{
	t_lexer 	*lexer;
	t_tokenlist	*tokenlist;
	char		*input;
	t_parser *parser;
	t_command *cmdlist;

	//input = get_line();
	//printf("input is:%s\n", input);
	//free(input);
	input = "ls -l | cat ";
	lexer = lexer_init(input);
	printf("input: %s\n", lexer->input);
	tokenlist = tokenlist_init();
	lexer_process_input(lexer, tokenlist);
	lexer_free(lexer);
	tokenlist_print(tokenlist->head);
	parser = parser_init(tokenlist);
	cmdlist = parse(parser, tokenlist);
	//execute();
	tokenlist_free(tokenlist);
	//parser_free();
	
	return (0);
}