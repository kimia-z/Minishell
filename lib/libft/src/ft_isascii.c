/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>                       +#+         */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:13:07 by ykarimi       #+#    #+#                 */
/*   Updated: 2023/11/03 19:52:03 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of isascii - test for ASCII character.
** Standard C Library (libc, -lc)
** #include <ctype.h>
** The isascii() function tests for an ASCII character, which is any character
** between 0 and octal 0177 inclusive.
*/
#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
