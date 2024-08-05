#include "lexer.h"



int main()
{
	t_lexer *lexer;
	char    input[70] = " hello 'echo $PATH' meow \"bah $LOGNAME bah\" bye p < >";

	lexer = lexer_init(input);
	printf("input: %s\n", lexer->input);
	lexer_process_input(lexer);
	lexer_free(lexer);
	
	return (0);
}