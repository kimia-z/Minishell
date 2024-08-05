/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:10:43 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:21:22 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of isalnum - alphanumeric character test.
** Standard C Library (libc, -lc)
** #include <ctype.h>
** The isalnum() function tests for any character for which isalpha(3) or
** isdigit(3) is true. The value of the
** argument must be representable as an unsigned char or the value of EOF.
*/
#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
