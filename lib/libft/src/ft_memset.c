/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:36:36 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:27:33 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of memset - fill a byte string with a byte value.
** Standard C Library (libc, -lc)
** #include <string.h>
** writes len bytes of value c (converted to an unsigned char) to the string b.
** returns its first argument.
*/
#include "libft.h"

void	*ft_memset(void *buffer, int value, size_t len)
{
	unsigned char	*buffer_ptr;

	buffer_ptr = buffer;
	while (len > 0)
	{
		*buffer_ptr = (unsigned char)value;
		buffer_ptr++;
		len--;
	}
	return (buffer);
}
