/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_islower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/05 18:30:47 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/01/05 18:36:25 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of islower function - lower-case character test
** Standard C Library
** #include <ctype.h>
** The islower() function returns zero if the character tests false and 
** returns non-zero if the character tests true.
*/

#include "libft.h"

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}
