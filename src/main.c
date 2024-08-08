#include "lexer.h"
#include "parser.h"

// static void operator_check(t_tokenlist *tokenlist)
// {
// 	t_token *temp;

// 	temp = tokenlist->head;
// 	while ( temp != NULL)
// 	{
// 		printf("token: %s\n",temp->value);
// 		if (temp->type == TOKEN_OP_PIPE)
// 			printf("yes\n");
// 		temp = temp->next;
// 	}


// }





static void    parser(t_tokenlist *tokenlist)
{
  
    print_token_list(tokenlist->head);
	syntax_checker(tokenlist);
   
   
}


int main()
{
	t_lexer 	*lexer;
	t_tokenlist	*tokenlist;

	char input[70] = "ls wc > ";

	lexer = lexer_init(input);
	printf("input: %s\n", lexer->input);
	tokenlist = tokenlist_init();
	lexer_process_input(lexer, tokenlist);
	lexer_free(lexer);
	parser(tokenlist);
	tokenlist_free(tokenlist);
	
	return (0);
}