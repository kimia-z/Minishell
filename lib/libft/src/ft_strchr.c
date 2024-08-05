/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:22:02 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/05/30 18:06:05 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of strchr - Locate character in string
** Standard C Library (libc, -lc)
** #include <string.h>
** The strchr() function returns a pointer to the first occurrence of the 
** character c in the string s.
** returns a pointer  to  the  matched character or NULL if the character 
** is not found.  The terminating null byte is considered part of the 
** string, so that if  c  is  specified  as
** '\0', these functions return a pointer to the terminator.
*/
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*string;
	unsigned char	value;
	if (!s)
		return (NULL);
	string = (char *)s;
	value = c;
	while (*string != value && *string != '\0')
		string++;
	if (*string == value)
		return (string);
	else
		return (NULL);
}
