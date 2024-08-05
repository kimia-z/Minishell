/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 10:48:31 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:24:14 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of tolower - upper case to lower case letter conversion.
** Standard C Library (libc, -lc)
** #include <ctype.h>
** If the argument is an upper-case letter, the tolower() function returns 
** the corresponding lower-case letter if there is one; otherwise, the argument
** is returned unchanged.
*/
#include "libft.h"

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 32);
	return (c);
}
