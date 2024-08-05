/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:17:27 by ykarimi       #+#    #+#                 */
/*   Updated: 2023/11/03 19:53:30 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_striteri.
** 
** Parameters :
** s : The string on which to iterate.
** f : The function to apply to each character.
** 
** Return value :
** None.
**
** Description :
** 
** Applies the function ’f’ on each character of the string passed as 
** argument, passing its index
** as first argument. Easch character is passed by address to ’f’ to 
** be modified if necessary.
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
