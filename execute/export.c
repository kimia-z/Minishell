#include <lexer.h>

void	print_export(t_lexer *lexer, int outfile)
{

}

/**
 * ft_export - Handles the export of environment variables in the shell.
 * 1) either display all environment variables in the current shell 
 *  or to add/update environment variables based on the provided
 * arguments. If arguments are provided, it validates each argument to ensure
 * it follows the correct format for environment variable assignments, 
 * and then adds or updates the variables accordingly.
 */

void	ft_export(t_lexer *lexer)
{
	int	outfile;
	int	i;

	i = 1;
	//outfile = lexer.outfile;
	if (!outfile)
	{
		outfile = STDOUT_FILENO;
	}
	if (lexer->tokens[1] == NULL)
	{
		print_export(lexer, outfile);
		return ;
	}
	while (lexer->tokens[i])
	{

		i++;
	}
}