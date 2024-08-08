#include "parser.h"
#include "lexer.h"

t_node *parse_pipeline(t_tokenlist *tokenlist, t_node *root, size_t token_pos)
{
	//t_node *redirect = NULL;
	t_node *left;
	t_node *right;

	root = add_node(pipeline);
	if (root == NULL)
		printf("root null from pipe func\n");
	left = add_node(command);
	right = add_node(command);
	root->left = left; // get the first command
	root->right = right; // get the second command

	left = parse_command();
	right = parse_comamnd();
	// redirection withing the pipeline
	// if (is_redirection(tokenlist))
	// {
	// 	redirect = add_node(redirection);
	// 	redirect->left = root->left;
	// 	redirect->right = add_node(file);
	// 	root->left = redirect;
	// }
	return (root);
}

t_node	*parse_redirection(t_tokenlist *tokenlist, t_node *root)
{
	root = add_node(redirection);
	root->left = add_node(command); //parse_command(tokenlist);
	root->right = add_node(file);
	return (root);
}


/* 
	do a syntax check
	create nodes for tree
	semantic check - validity of tokens(commands and arguments)(define these rules)
*/
void    parser(t_tokenlist *tokenlist)
{
	t_node *root;
	size_t token_pos;
	token_pos = 0;
	root = NULL;
	//tokenlist_print(tokenlist->head);
	if (syntax_checker(tokenlist) == 1)
	{
		printf("error\n");
		tokenlist_free(tokenlist);
		exit(EXIT_FAILURE);
	}

	// at this point, things should be sorta ready for tree
	// decide what gets to be the root node

	token_pos = is_pipeline(tokenlist);
	if (token_pos >= 0)
	{
		root = parse_pipeline(tokenlist, root, token_pos);

	}
	if (root == NULL)
		printf("root null\n");
	// int i = 0;
	// t_node *temp = root;
	// while (temp != NULL)
	// {
	// 	printf("%d  - ", i);

	// 	printf("Node rule: %d, Token Value: %s\n", temp->rule, temp->path);
	// 	//temp = temp->next;
	// 	i++;
	// }
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