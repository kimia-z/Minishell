#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// getline allocates with malloc. free when you're done
/*  readline  returns  the text of the line read.  A blank line returns the
       empty string.  If EOF is encountered while reading a line, and the line
       is  empty,  NULL is returned.  If an EOF is read with a non-empty line,
       it is treated as a newline.
*/

int     get_line()
{
    char *line;
    while (true)
    {
        line = get_line();
        if (line)
            //do sth
    }
    return ();
}

// char	*get_line()
// {
// 	char	*input;

// 	input = readline("Minishell: ");
// 	if (!input)
// 	{
// 		return (NULL);
// 	}
// 	return (input);
// }
