/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:14:54 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 20:45:38 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_strjoin.
** 
** Parameters : 
** s1 : The prefix string.
** s2 : The suffix string.
**
** Return value :
** The new string. NULL if the allocation fails.
**
** Description :
** Allocates (with malloc(3)) and returns a new string, which is the result of 
** the concatenation of ’s1’ and ’s2’.
*/
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	total_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_len + 1);
	ft_strlcat(result, s2, total_len + 1);
	return (result);
}
