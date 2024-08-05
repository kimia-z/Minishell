/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/05 18:33:56 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/01/05 18:34:22 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of isspace function - white-space character test
** Standard C Library
** #include <ctype.h>
** The isspace() function returns zero if the character tests false and 
** returns non-zero if the character tests true.
** white-space characters include : ' ', '\t', '\n', '\v', '\f', '\r'
*/

#include "libft.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
