/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:38:12 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 20:39:48 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of memmove - copy memory area
** Standard C Library (libc, -lc)
** #include <string.h>
** The  memmove()  function  copies n bytes from memory area src to memory
** area dest.  The memory areas may overlap: copying takes place as though
** the  bytes in src are first copied into a temporary array that does not
** overlap src or dest, and the bytes are then copied from  the  temporary
** array to dest.
** The memmove() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!src && len > 0)
		return (NULL);
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			((unsigned char *)dst)[len] = ((const unsigned char *)src)[len];
		}
	}
	else
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
