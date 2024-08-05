/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 12:27:44 by ykarimi       #+#    #+#                 */
/*   Updated: 2023/12/05 16:13:28 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_lstdelone
** 
** Parameters : 
** lst : The node to free.
** del : The address of the function used to delete the content.
**
** Return value :
** None.
**
** Description :
** Takes as a parameter a node and frees the memory of
** the node’s content using the function ’del’ given as a parameter 
** and free the node. The memory of ’next’ must not be freed.
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (lst->content != 0 && del != 0)
		(*del)(lst->content);
	free(lst);
}
