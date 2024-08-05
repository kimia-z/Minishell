/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:02:36 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/03/25 11:25:37 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of strncmp - Compare strings.
** Standard C Library (libc, -lc)
** #include <string.h>
** compares not more than n characters.  Because strncmp() is designed for 
** comparing strings rather than binary data, characters that appear after a
** ‘\0’ character are not compared.
** returns an integer greater than, equal to, or less than 0, according as
** the string s1 is greater than, equal to, or less than the string s2.  
** The comparison is done using unsigned
** characters, so that ‘\200’ is greater than ‘\0’.
*/
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	if (s1p == 0 && s2p == 0)
		return (0);
	while (n > 0 && *s1p && *s2p && (*s1p == *s2p))
	{
		s1p++;
		s2p++;
		n--;
	}
	if (n == 0 || (*s1p == '\0' && *s2p == '\0'))
		return (0);
	else
		return (*s1p - *s2p);
}
