#include "parser.h"

/* Creates a new node */
t_node	*create_node()
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	ft_bzero(new_node, sizeof(t_node));
	return (new_node);
}

void    free_node()
{
    if ()
    {
        free();
    }
}

