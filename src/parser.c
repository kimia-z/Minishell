#include "parser.h"

t_node *parse_pipeline(t_tokenlist *tokenlist, t_node *tree)
{
	t_node *root;
	t_node *left;
	t_node *right;
	t_node *redirect;

	root = create_node(pipe, );
	root->left = parse_command(); // get the first command
	root->right = parse_comamnd(); // get the second command
	// redirection withing the pipeline
	if (is_redirection(tokenlist))
	{
		redirect = create_node(redirection, );
		redirect->left = root->left;
		redirect->right = create_node(file, get_filename(tokenlist));
		root->left = redirect;

	}
	

}


t_node	*parse_redirection(t_tokenlist *tokenlist)
{
	t_node *root;
	t_node *right;
	t_node *left;
	root = create_node(redirection, NULL);
	root->left = parse_command(tokenlist);
	root->right = create_node(file, get_filename(tokenlist));
}





/* 
    do a syntax check
    create nodes for tree
    semantic check - validity of tokens(commands and arguments)(define these rules)
*/
void    parser(t_tokenlist *tokenlist)
{
    t_node *tree;
  
    print_token_list(tokenlist->head);
	if (syntax_checker(tokenlist) == 1)
    {
        tokenlist_free(tokenlist);
        exit(EXIT_FAILURE);
    }
	tree = create_tree();
    // at this point, things should be sorta ready for tree
    // decide what gets to be the root ndoe
    if (is_pipeline(tokenlist))
    {
        tree = parse_pipeline(tokenlist, tree);

    }
    else if (is_redirection(tokenlist))
    {
        tree = parse_redirection(tokenlist);

    }
    //else if subshell
    else if (is_command(tokenlist))
    {
        tree = parse_command(tokenlist);
    }



   
}