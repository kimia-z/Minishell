/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/23 13:52:31 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 14:09:10 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*h_sub;
	const char	*n;

	if (!*needle)
	{
		return ((char *)haystack);
	}
	h = haystack;
	while (*h)
	{
		h_sub = h;
		n = needle;
		while (*h_sub && *n && *h_sub == *n)
		{
			h_sub++;
			n++;
		}
		if (!*n)
		{
			return ((char *)h);
		}
		h++;
	}
	return (NULL);
}
