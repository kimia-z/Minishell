#include "lexer.h"
#include "parser.h"

int main()
{
	t_lexer 	*lexer;
	t_tokenlist	*tokenlist;

	char input[70] = "   hello meow hi \"kimia\" bye";

	lexer = lexer_init(input);
	printf("input: %s\n", lexer->input);
	tokenlist = tokenlist_init();
	lexer_process_input(lexer, tokenlist);
	lexer_free(lexer);
	parser(tokenlist);
	tokenlist_free(tokenlist);
	
	return (0);
}