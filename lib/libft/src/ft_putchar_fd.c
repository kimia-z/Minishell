/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:26:39 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:22:36 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft)putchar_fd.
**
** Parameters :
** c : The character to output
** fd : The file descriptor on which to write.
** 
** Return value :
** None.
** 
** Description :
** Outputs the character ’c’ to the given file descriptor.
*/
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
