/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 12:28:28 by ykarimi       #+#    #+#                 */
/*   Updated: 2023/11/06 08:41:16 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_lstmap
** 
** Parameters : 
** lst : The address of a pointer to a node.
** f : The address of the function used to iterate on the list.
** del : The address of the function used to delete the content of a
** node if needed.
**
** Return value :
** None.
**
** Description :
** Iterates the list ’lst’ and applies the function ’f’ on the content of 
** each node.
** Creates a new list resulting of the successive applications of 
** the function ’f’. 
** The ’del’ function is used to delete the content of a node if needed.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	ptr = new_list;
	lst = lst->next;
	while (lst != NULL)
	{
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&ptr, del);
			return (NULL);
		}
		lst = lst->next;
		new_list = new_list->next;
	}
	return (ptr);
}
