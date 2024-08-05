/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 12:27:57 by ykarimi       #+#    #+#                 */
/*   Updated: 2023/11/03 19:54:43 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_lstclear
** 
** Parameters : 
** lst : The address of a pointer to a node.
** del : The address of the function used to delete the content of the node.
**
** Return value :
** None.
**
** Description :
** Deletes and frees the given node and every successor of that node, 
** using the function ’del’ and free(3).
** Finally, the pointer to the list must be set to NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*traverse;

	traverse = *lst;
	while (traverse != NULL)
	{
		traverse = traverse->next;
		ft_lstdelone(*lst, del);
		*lst = traverse;
	}
	lst = NULL;
}
