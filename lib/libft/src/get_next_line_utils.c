/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:26:57 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/19 10:54:49 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ftt_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	total_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (total_len + 1));
	if (result == NULL)
		return (free(s1), NULL);
	while (s1 && s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*allocate_memory(int i)
{
	char	*extracted_line;

	extracted_line = malloc(sizeof(char) * (i + 1));
	if (extracted_line == NULL)
		return (NULL);
	return (extracted_line);
}
