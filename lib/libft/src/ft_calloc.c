/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:08:41 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:21:15 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of calloc() - Memory allocation
** #include <stdlib.h>
** The allocated memory is aligned such that it can be used for any data type,
** including AltiVec- and SSE-related types.
** The calloc() function contiguously allocates enough space for count objects
** that are size bytes of memory each and returns a pointer to the allocated 
** memory.  The allocated memory is filled with bytes of value zero.
** return a pointer to allocated memory.  If there is an error, they return
** a NULL pointer and set errno to ENOMEM
*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	max_size;

	mem = NULL;
	max_size = (size_t) - 1;
	if (count == 0 || size == 0)
		return (malloc(0));
	if (max_size / size < count)
		return (NULL);
	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}
