#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// getline allocates with malloc. free when you're done
/*  readline  returns  the text of the line read.  A blank line returns the
       empty string.  If EOF is encountered while reading a line, and the line
       is  empty,  NULL is returned.  If an EOF is read with a non-empty line,
       it is treated as a newline.
*/



/*
    lexer 
    parser
    executor
    preliminary cleanup if needed
*/
void process_commandline(char *input)
{
    printf("Executing: %s\n", input);
    // data->lexer = lexer(data, line);
    // if ()
    //     return ;
    // data->parser = parser();
    // if ()
    //     return ; // or assign error
    // executor();
    // free things;
    // tokenlist_free(tokenlist);
	// free(parser);
	// free_command_list(cmdlist);
    // return ();
}





// int bridge_function(void)
// {
// 	t_lexer 	*lexer;
// 	t_tokenlist	*tokenlist;
// 	char		*input;
// 	t_parser *parser;
// 	t_command *cmdlist;

// 	//input = get_line();
// 	//printf("input is:%s\n", input);
// 	//free(input);

// 	input = "echo hello | ls > out | wc -l";
// 	lexer = lexer_init(input);
// 	printf("input: %s\n", lexer->input);
// 	tokenlist = tokenlist_init();
// 	lexer_process_input(lexer, tokenlist);
// 	lexer_free(lexer);
// 	tokenlist_print(tokenlist->head);
// 	parser = parser_init(tokenlist);
// 	cmdlist = parse(parser, tokenlist);
// 	print_command_list(cmdlist);
// 	printf("\n\n");
// 	//execute();

// 	tokenlist_free(tokenlist);
// 	free(parser);
// 	free_command_list(cmdlist);
	
// 	return (0);
// }
