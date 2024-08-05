/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:27:02 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:22:41 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_putendl_fd.
** 
** Parameters :
** s : The string to output.
** fd : The file descriptor on which to write.
** 
** Return value :
** None.
** 
** Description :
** Outputs the string ’s’ to the given file descriptor followed by a newline.
*/
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s == 0)
		return ;
	while (s[i] != 0)
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}
