/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:12:41 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:23:20 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of strlcat function - Size-bounded string concatenation.
** library "libbsd"
** #include <bsd/string.h>
** strlcat() takes the full size of the buffer (not just the length) and 
** guarantee to NUL-terminate the result (as long as size is larger than 0 or,
** in the case of strlcat(), as long as there is at least one byte free in dst)
** Note that a byte for the NUL should be included in size.
** return value is the initial length of dst plus the length of src.
** If the return value is >= dstsize, the output string has been truncated. 
** It is the caller's responsibility to handle this.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;

	d_len = 0;
	while (d_len < size && dst[d_len] != 0)
		d_len++;
	if (d_len == size)
		return (size + ft_strlen(src));
	s_len = ft_strlcpy(dst + d_len, src, size - d_len);
	return (d_len + s_len);
}
