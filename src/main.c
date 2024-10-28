#include "lexer.h"
#include "parser.h"
#include "minishell.h"



void	init_minishell(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	//init fds if you wish to keep them in t_data struct

}


/*
	do we need a while(true) loop in here? 
	interative -> input from a terminal 
	non-interative input from a file or pipe
*/
int main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;

	init_minishell(&data);
	init_env(&data, envp);

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
