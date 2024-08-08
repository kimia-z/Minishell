#include "parser.h"
#include "lexer.h"

t_node *parse_pipeline(t_tokenlist *tokenlist, t_node *root)
{
	t_node *redirect = NULL;

	root = add_node(pipeline);
	if (root == NULL)
		printf("root null from pipe func\n");
	root->left = add_node(command); // get the first command
	root->right = add_node(command); // get the second command

	// redirection withing the pipeline
	if (is_redirection(tokenlist))
	{
		redirect = add_node(redirection);
		redirect->left = root->left;
		redirect->right = add_node(file);
		root->left = redirect;
	}
	return (root);
}

t_node	*parse_redirection(t_tokenlist *tokenlist, t_node *root)
{
	root = add_node(redirection);
	root->left = add_node(command); //parse_command(tokenlist);
	root->right = add_node(file);
}


/* 
	do a syntax check
	create nodes for tree
	semantic check - validity of tokens(commands and arguments)(define these rules)
*/
void    parser(t_tokenlist *tokenlist)
{
	t_node *root;
	root = NULL;
	//tokenlist_print(tokenlist->head);
	if (syntax_checker(tokenlist) == 1)
	{
		printf("error\n");
		tokenlist_free(tokenlist);
		exit(EXIT_FAILURE);
	}
	// at this point, things should be sorta ready for tree
	// decide what gets to be the root ndoe
	if (is_pipeline(tokenlist))
	{
		root = parse_pipeline(tokenlist, root);

	}
	if (root == NULL)
		printf("root null\n");
	int i = 0;
	t_node *temp = root;
	while (temp != NULL)
	{
		printf("%d  - ", i);

		printf("Node rule: %d, Token Value: %s\n", temp->rule, temp->path);
		//temp = temp->next;
		i++;
	}
	// else if (is_redirection(tokenlist))
	// {
	//     tree = parse_redirection(tokenlist);

	// }
	// //else if subshell
	// else if (is_command(tokenlist))
	// {
	//     tree = parse_command(tokenlist);
	// }




}