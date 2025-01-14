/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kziari <kziari@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 11:10:16 by kziari        #+#    #+#                 */
/*   Updated: 2024/12/23 14:24:38 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <string.h>

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

static int	newline_helper(char *temp, bool nline, int *count)
{
	int	i;

	i = 1;
	while (temp[i] && temp[i] == 'n')
		i++;
	if (temp[i - 1] == 'n' && !temp[i])
		nline = false;
	else if (temp[i - 1] == 'n' && temp[i] && temp[i] != ' ')
	{
		(*count)--;
		return (-1);
	}
	return (0);
}

static void	error_echo(t_data *data)
{
	write_stderr("echo: invalid file descriptor");
	data->exit_status = ERROR_GENERIC;
}

static bool	check_newline(t_command *commands, int *pos, int count, bool nline)
{
	char	*temp;

	while (commands->command[count] && commands->command[count][0] == '-')
	{
		temp = commands->command[count];
		count++;
		if (ft_strncmp(temp, "-n", 3) == 0)
			nline = false;
		else if (ft_strncmp(temp, "-n", 2) == 0)
		{
			if (newline_helper(temp, nline, &count) == -1)
				break ;
			else
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

static void	print_echo(t_data *data, t_command *commands, int outfile, int *pos)
{
	char	*arg;
	char	*exit_code_str;
	char	*result;

	arg = commands->command[*pos];
	if (commands->is_quotes[*pos])
		ft_putstr_fd(arg, outfile);
	else
	{
		exit_code_str = ft_itoa(data->exit_status);
		result = ft_strdup(arg);
		handle_exit_code(&result, exit_code_str, arg);
		ft_putstr_fd(result, outfile);
		free(result);
		free(exit_code_str);
	}
	if (commands->command[++(*pos)])
		ft_putchar_fd(' ', outfile);
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
	while (commands->command[position])
		print_echo(data, commands, outfile, &position);
	if (is_newline)
		ft_putchar_fd('\n', outfile);
	data->exit_status = SUCCESS;
}
