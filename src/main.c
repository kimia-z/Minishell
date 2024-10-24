#include "lexer.h"
#include "parser.h"
#include "minishell.h"


/*
	do we need a while(true) loop in here? 
	interative -> input from a terminal 
	non-interative input from a file or pipe
*/
int main()
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
    global_data = &data;
	// set_signals(); sigint - sigquit - sigwinch
	//get_env_var(data);

	if (isatty(STDIN_FILENO) == 1) //if input is from a terminal
		interactive_shell(&data); //termcap lib - prompt
	else
		non_interactive();
	//cleanup(data);
	return (data.exit_status);
}
