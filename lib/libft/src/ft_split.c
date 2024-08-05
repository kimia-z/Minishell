/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:23:19 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:23:04 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_split
** 
** Parameters :
** 
** s: The string to be split.
** c: The delimiter character.
** 
** Return value :
** 
** The array of new strings resulting from the split.
** NULL if the allocation fails
** 
** Description :
** 
** Allocates (with malloc(3)) and returns an array of strings obtained 
** by splitting ’s’ using the character ’c’ as a delimiter. 
** The array must end
** with a NULL pointer.
*/

#include "libft.h"

static unsigned int	num_of_substrings(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static char	*create_substrings(char const *s, char c)
{
	char	*string;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	string = malloc (len + 1);
	if (!string)
		return (NULL);
	while (i < len)
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static void	free_things(char **ptr)
{
	unsigned int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
	}
	free(ptr);
}

char	**fill_substrings(char const *s, char **str, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			str[i] = create_substrings(s, c);
			if (str[i] == NULL)
			{
				free_things(str);
				return (NULL);
			}
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char		**ptr;

	ptr = ft_calloc(sizeof(char *), (num_of_substrings(s, c)) + 1);
	if (!ptr)
		return (NULL);
	return (fill_substrings(s, ptr, c));
}
