/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:14:16 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:20:54 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementing isdigit - decimal-digit character test.
** Standard C Library (libc, -lc)
** #include <ctype.h>
** The isdigit() function tests for a decimal digit character.  Regardless of 
** locale, this includes the following characters only:
** 
**  ``0''``1''``2''``3''``4''
**  ``5''``6''``7''``8''``9''
** 
** return zero if the character tests false and return non-zero if the 
** character tests true.
*/

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
