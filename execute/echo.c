#include "lexer.h"

/* This function will check if the ECHO is called
	with -n options 
	example: echo -n hi
			 echo -nnnnnn hi
			 echo -n -n -n hi
*/

static bool	check_newline(t_lexer *lexer, int *position)
{
	bool	newline;
	int		count;
	char	*temp;
	int		i;

	newline = true;
	count = 1;
	while (lexer->tokens[count] && lexer->tokens[count]->value[0] == '-')
	{
		i = 1;
		temp = lexer->tokens[count];
		count++;
		if (strcmp(temp, "-n") == 0)
		{
			newline = false;
		}
		else if (ft_strncmp(temp, "-n", 2) == 0)
		{
			while (temp[i] && temp[i] == 'n')
			{
				i++;
			}
			if (temp[i - 1] == 'n' && !temp[i])
			{
				newline = false;
			}
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

void	ft_echo(t_lexer *lexer)
{
	int		outfile;
	bool	is_newline;
	int		position;

	//outfile = lexer.outfile;
	position = 1;
	if (!outfile)
		outfile = STDOUT_FILENO;
	is_newline = check_newline(lexer, &position);
	while (lexer->tokens[position])
	{
		write(outfile, lexer->tokens[position], ft_strlen(lexer->tokens[position]));
		if (lexer->tokens[++position])
		{
			write(outfile, " ", 1);
		}
	}
	if (check_newline)
	{
		write(outfile, "\n", 1);
	}
}