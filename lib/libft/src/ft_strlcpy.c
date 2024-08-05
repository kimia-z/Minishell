/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:11:04 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/03/25 11:24:35 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of strlcpy function - size-bounded string copying
** library "libbsd"
** #include <bsd/string.h>
** The strlcpy() first appeared in OpenBSD 2.4, and FreeBSD 3.3.
** It was designed to be safer, more consistent, and less error prone 
** replacement for the easily misused function strncpy(3).
** strlcpy() copies up to dstsize - 1 characters from the string src to dst,
** NUL-terminating the result if dstsize is not 0. Returns the length of src.
*/
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0 && dst != src)
	{
		while (i < size - 1 && src[i] != 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i] != 0)
		i++;
	return (i);
}
