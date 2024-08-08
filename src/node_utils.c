#include "parser.h"

/* Creates a new node */
t_node	*add_node(rule rule)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	// ft_bzero(new_node, sizeof(t_node));
    node->rule = rule;
    node->args = NULL;
    node->path = NULL;
    node->fds[0] = -1;
    node->fds[1] = -1;
    node->right = NULL;
    node->left = NULL;

	return (node);
}

// void    free_node()
// {
//     if ()
//     {
//         free();
//     }
// }

ls 
-l 
file1 
|
wc


        root
        pipe
      /     \
   cmd       cmd

