/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/05 18:32:07 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/01/05 18:35:51 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of isupper function - upper-case character test
** Standard C Library
** #include <ctype.h>
** The isupper() function returns zero if the character tests false and 
** returns non-zero if the character tests true
*/

#include "libft.h"

int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}
