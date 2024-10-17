#include "lexer.h"
#include "parser.h"


static void print_command_list(t_command *cmdlist)
{
    t_command *current = cmdlist;
    int i;

    while (current != NULL)
    {
        printf("Command: %s\n", current->command);
        printf("Arguments: ");
        if (current->args != NULL)
        {
            for (i = 0; current->args[i] != NULL; i++)
            {
                printf("%s ", current->args[i]);
            }
        }
        printf("\n");

        if (current->redirect_in != NULL)
            printf("Redirect In: %s\n", current->redirect_in);
        if (current->redirect_out != NULL)
            printf("Redirect Out: %s\n", current->redirect_out);
        if (current->redirect_append != NULL)
            printf("Redirect Append: %s\n", current->redirect_append);
		    if (current->path != NULL)
            printf("Path: %s\n", current->path);

        current = current->next;
        printf("\n");
    }
}


int bridge_function(void)
{
	t_lexer 	*lexer;
	t_tokenlist	*tokenlist;
	char		*input;
	t_parser *parser;
	t_command *cmdlist;

	//input = get_line();
	//printf("input is:%s\n", input);
	//free(input);

	input = "echo hello | ls > out | wc -l";
	lexer = lexer_init(input);
	printf("input: %s\n", lexer->input);
	tokenlist = tokenlist_init();
	lexer_process_input(lexer, tokenlist);
	lexer_free(lexer);
	tokenlist_print(tokenlist->head);
	parser = parser_init(tokenlist);
	cmdlist = parse(parser, tokenlist);
	print_command_list(cmdlist);
	printf("\n\n");
	//execute();

	tokenlist_free(tokenlist);
	free(parser);
	free_command_list(cmdlist);
	
	return (0);
}
