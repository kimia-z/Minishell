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
static bool	check_newline(t_command *commands, int *position)
{
	bool	newline;
	int		count;
	char	*temp;
	int		i;

	newline = true;
	count = 1;
	while (commands->command[count] && commands->command[count][0] == '-')
	{
		i = 1;
		temp = commands->command[count];
		count++;
		if (ft_strncmp(temp, "-n", 3) == 0)
			newline = false;
		else if (ft_strncmp(temp, "-n", 2) == 0)
		{
			while (temp[i] && temp[i] == 'n')
				i++;
			if (temp[i - 1] == 'n' && !temp[i])
				newline = false;
		}
		else
		{
			count--;
			break;
		}
	}
	(*position) = count;
	return (newline);
}

int	ft_echo(t_command *commands, t_data *data)
{
	int		outfile;
	bool	is_newline;
	int		position;

	if (commands->outfile_fd == -2)
		outfile = STDOUT_FILENO;
	else
		outfile = commands->outfile_fd;
	if (outfile < 0)
	{
		ft_putstr_fd("echo: invalid file descriptor\n", STDERR_FILENO);
		data->exit_status = ERROR_GENERIC;
		return (-1);
	}
	position = 1;
	is_newline = check_newline(commands, &position);
	while (commands->command[position])
	{
		ft_putstr_fd(commands->command[position], outfile);
		if (commands->command[++position])
			ft_putchar_fd(' ', outfile);
	}
	if (is_newline)
		ft_putchar_fd('\n', outfile);
	data->exit_status = 0;
	return (0);
}
