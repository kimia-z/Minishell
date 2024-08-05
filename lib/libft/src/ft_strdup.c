/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:18:54 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:23:10 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of strdup - save a copy of a string
** #include <string.h>
** Standard C Library
** duplicate a string from one memory location to anotehr memory location
** The strdup() function allocates sufficient memory for a copy of the string
** s1, does the copy, and returns a pointer to it.  The pointer may subsequently
** be used as an argument to the function free(3).
** If insufficient memory is available, NULL is returned and errno is set to
**  ENOMEM.
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	ft_memcpy(str, s, len + 1);
	return (str);
}
