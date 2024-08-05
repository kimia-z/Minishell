/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:41:58 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:25:19 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of memcmp - compare memory areas
** Standard C Library (libc, -lc)
** #include <string.h>
** compares the first n bytes (each interpreted as unsigned  char) of the 
** memory areas s1 and s2.
** returns  an  integer  less  than,  equal  to,  or greater than zero if 
** the first n bytes of s1 is found, respectively, to be less than, to match, 
** or be greater than the first n bytes of s2.
** For a nonzero return value, the sign is determined by the sign  of  the 
** difference  between  the  first  pair of bytes (interpreted as unsigned char)
** that differ in s1 and s2.
** If n is zero, the return value is zero.
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*s1p != *s2p)
			return (*s1p - *s2p);
		s1p++;
		s2p++;
		n--;
	}
	return (0);
}
