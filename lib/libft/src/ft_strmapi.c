/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:05:42 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:23:36 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_strmapi.
** 
** Parameters : 
** s : The string on which to iterate.
** f : The function to apply to each character.
** 
** Return value :
** The string created from the successive applications of ’f’.
** Returns NULL if the allocation fails.
**
** Description :
** Applies the function ’f’ to each character of the string ’s’, and 
** passing its
** index as first argument to create a new string (with malloc(3)) 
** resulting from successive applications of ’f’.
*/
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	size_t	i;
	char	*result;

	if (s == 0 || f == 0)
		return (0);
	s_len = ft_strlen(s);
	i = 0;
	result = (char *)malloc(sizeof(char) * (s_len + 1));
	if (result == NULL)
		return (NULL);
	result[s_len] = '\0';
	while (s[i])
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	return (result);
}
