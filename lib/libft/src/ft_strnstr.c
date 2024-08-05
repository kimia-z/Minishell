/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 10:59:17 by ykarimi       #+#    #+#                 */
/*   Updated: 2023/11/03 19:49:19 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of strnstr - locate a substring in a string
** Utility function from BSD systems - libbsd, -lbsd
** #include <string.h>
** function locates the first occurrence of the null-termi‐nated string 
** little in the string big, where not more than len characters are searched. 
** Characters that appear after a ‘\0’ character are not searched.
** If little is an empty string, big is returned; if little occurs nowhere 
** in big, NULL is returned; otherwise a pointer to the first character of
** the first occurrence of little is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (!*little)
		return ((char *) big);
	if (len == 0)
		return (0);
	little_len = ft_strlen(little);
	while (*big && len && (len >= little_len))
	{
		if (*big == *little && ft_strncmp(big, little, little_len) == 0)
			return ((char *) big);
		big++;
		len--;
	}
	return (NULL);
}
