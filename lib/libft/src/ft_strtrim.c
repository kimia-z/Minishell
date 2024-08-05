/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 10:52:17 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/03/25 14:45:54 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_strtrim.
** 
** Parameters :
** s1 : The string to be trimmed.
** set : The reference set of characters to trim.
** 
** Return value : 
** The trimmed string.
** NULL if the allocation fails.
**
** Description :
** Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
** specified in ’set’ removed
** from the beginning and the end of the string
*/

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	s1_len;

	if (set == 0 && s1 != 0)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1) != NULL)
		s1++;
	s1_len = ft_strlen(s1);
	if (s1_len == 0)
	{
		trimmed_str = malloc(1);
		if (!trimmed_str)
			return (NULL);
		trimmed_str[0] = '\0';
		return (trimmed_str);
	}
	while (s1_len && ft_strchr(set, s1[s1_len - 1]) != NULL)
		s1_len--;
	trimmed_str = malloc(sizeof(char) * (s1_len +1));
	if (!trimmed_str)
		return (NULL);
	ft_memcpy(trimmed_str, s1, s1_len);
	trimmed_str[s1_len] = '\0';
	return (trimmed_str);
}
