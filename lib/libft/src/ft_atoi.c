/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 15:49:13 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/05/27 16:40:01 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of atoi - Convert a string to an integer.
** Standard C Library (libc, -lc)
** #include <stdlib.h>
** The  atoi() function converts the initial portion of the string pointed to
** by nptr to int.
** The converted value or 0 on error.
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	n;
	int			is_negative;

	n = 0;
	is_negative = false;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		is_negative = (*str == '-');
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		n = (n * 10) + (*str - '0');
		if (is_negative && (-n < INT_MIN))
			return (INT_MIN);
		if (!is_negative && n > INT_MAX)
			return (INT_MAX);
		str++;
	}
	if (is_negative)
		return (-n);
	return (n);
}
