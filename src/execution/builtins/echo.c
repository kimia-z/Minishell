/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kziari <kziari@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 11:10:16 by kziari        #+#    #+#                 */
/*   Updated: 2024/12/10 18:57:20 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* This function will check if the ECHO is called
	with -n options 
	example: echo -n hi
			 echo -nnnnnn hi
			 echo -n -n -n hi
*/
// doesnt handle special characters (\t for example)
// doesnt handle invalid fd

/*
test case:
$echo hello > /dev/full
Collected operator token: >, type: 1
Collected operator token: /dev/full, type: 6

should behave as :
echo: write error\n or  minishel: operation not permitted: <directory>
*/

static void	error_echo(t_data *data)
{
	write_stderr("echo: invalid file descriptor");
	data->exit_status = ERROR_GENERIC;
}

static bool	check_newline(t_command *commands, int *pos, int count, bool nline)
{
	char	*temp;
	int		i;

	while (commands->command[count] && commands->command[count][0] == '-')
	{
		i = 1;
		temp = commands->command[count];
		count++;
		if (ft_strncmp(temp, "-n", 3) == 0)
			nline = false;
		else if (ft_strncmp(temp, "-n", 2) == 0)
		{
			while (temp[i] && temp[i] == 'n')
				i++;
			if (temp[i - 1] == 'n' && !temp[i])
				nline = false;
		}
		else
		{
			count--;
			break ;
		}
	}
	(*pos) = count;
	return (nline);
}

void	ft_echo(t_command *commands, t_data *data)
{
	int		outfile;
	bool	is_newline;
	int		position;
	int		count;
	bool	newline;

	count = 1;
	newline = true;
	if (commands->outfile_fd == -2)
		outfile = STDOUT_FILENO;
	else
		outfile = commands->outfile_fd;
	if (outfile < 0)
		return (error_echo(data));
	position = 1;
	is_newline = check_newline(commands, &position, count, newline);
	if(ft_strncmp(commands->command[position], "$?", 2) == 0)
		ft_putnbr_fd(data->exit_status, outfile);
	else
	{
		while (commands->command[position])
		{
			// if(ft_strncmp(commands->command[position], "$?", 2) == 0)
			// 	ft_putnbr_fd(data->exit_status, outfile);
			ft_putstr_fd(commands->command[position], outfile);
			if (commands->command[++position])
				ft_putchar_fd(' ', outfile);
		}
	}
	if (is_newline)
		ft_putchar_fd('\n', outfile);
	data->exit_status = SUCCESS;
}
