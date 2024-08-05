/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:39:58 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:22:15 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of memcpy - copy memory area
** Standard C Library (libc, -lc)
** #include <string.h>
** copies n bytes from memory area src to memory area dst.  If dst and src 
** overlap, behavior is undefined.  Applications in which dst and src might 
** overlap should use memmove(3) instead.
** returns the original value of dst.
*/
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (dst == src)
		return (dst);
	dst_ptr = dst;
	src_ptr = src;
	while (n)
	{
		*dst_ptr = *src_ptr;
		src_ptr++;
		dst_ptr++;
		n--;
	}
	return (dst);
}
