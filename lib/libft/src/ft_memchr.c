/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:28:44 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:22:10 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of memchr - scan memory for a character
** Standard C Library (libc, -lc)
** #include <string.h>
** scans  the  initial n bytes of the memory area pointed to by s for the 
** first instance of c.
** Both c and the  bytes  of the memory area pointed to by s are interpreted 
** as unsigned char.
** returns a pointer to the matching byte or NULL if the character does not 
** occur in the given memory area.
*/

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*src_ptr;
	unsigned char	value;
	size_t			i;

	src_ptr = (unsigned char *) src;
	value = (unsigned char) c;
	i = 0;
	if (!src)
		return (NULL);
	while (i < n)
	{
		if (src_ptr[i] == value)
			return ((void *)&src_ptr[i]);
		i++;
	}
	return (NULL);
}
