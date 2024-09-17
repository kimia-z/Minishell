#include "lexer.h"
#include "parser.h"
#include "minishell.h"


void    interactive_shel(t_data *data)
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

}