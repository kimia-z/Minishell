// #include "parser.h"

// /* Creates a new node */
// t_node	*create_new_node(int num)
// {
// 	t_node	*new_node;

// 	new_node = malloc(sizeof(t_node));
// 	if (new_node == NULL)
// 		return (NULL);
// 	ft_bzero(new_node, sizeof(t_node));
// 	return (new_node);
// }

// /* Checks for duplicate nodes */
// bool	is_node_duplicate(t_node *head, int num)
// {
// 	t_node	*temp;

// 	temp = head;
// 	while (temp != NULL)
// 	{
// 		if (temp->num == num)
// 			return (true);
// 		temp = temp->next;
// 	}
// 	return (false);
// }

