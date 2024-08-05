/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 16:15:42 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:34:55 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_itoa.
** 
** Parameters :
** n : the integer to convert.
** 
** Return value :
** The string representing the integer. 
** NULL if the allocation fails.
*
** Description :
** Allocates (withm alloc(3)) and returns a string representing the integer
** received as an argument.
** Negative numbers must be handled.
*/

#include "libft.h"

static int	get_length(int nb)
{
	size_t	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		count++;
	while (nb != 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*result;
	size_t			length;
	unsigned int	num;

	length = get_length(n);
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	result[length] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (length > 0)
	{
		if (result[length - 1] == '-')
			break ;
		result[length - 1] = (char)(num % 10 + '0');
		num /= 10;
		length--;
	}
	return (result);
}
