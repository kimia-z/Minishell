/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 12:28:16 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 17:44:33 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_lstiter
** 
** Parameters : 
** lst : The address of a pointer to a node.
** f : The address of the function used to iterate on the list.
**
** Return value :
** None.
**
** Description :
** Iterates the list ’lst’ and applies the function ’f’ on the content of 
** each node.
*/
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL && f != NULL)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
