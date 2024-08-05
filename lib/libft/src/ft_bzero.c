/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:06:18 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:21:09 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of bzero - write zeroes to a byte string.
** Standard C Library (libc, -lc)
** #include <strings.h>
** The bzero() function writes n zeroed bytes to the string s.  If n is zero,
** bzero() does nothing.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
