/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:33:35 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/01/05 18:25:42 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Implementation of ft_putnbr_fd.
** 
** Parameters : 
** n : The integer to output.
** fd : The file descriptor on which to write.
**
** Return value :
** None.
**
** Description : 
** Outputs the integer ’n’ to the given file descriptor.
*/

#include "libft.h"

static void	write_number(unsigned int n, int fd)
{
	char	c;

	if (n != 0)
	{
		c = n % 10 + '0';
		write_number(n / 10, fd);
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
		write(fd, "-", 1);
	if (n < 0)
		n = -n;
	write_number(n, fd);
}
