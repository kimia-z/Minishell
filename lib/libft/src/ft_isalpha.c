/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:12:15 by ykarimi       #+#    #+#                 */
/*   Updated: 2023/11/03 19:48:17 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of isalpha - alphabetic character test.
** Standard C Library (libc, -lc)
** #include <ctype.h>
** The isalpha() function returns zero if the character tests false and 
** returns non-zero if the character tests true.
*/
#include "libft.h"

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
