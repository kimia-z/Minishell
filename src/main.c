#include "lexer.h"
#include "parser.h"
#include "minishell.h"

read_line()
{

}



void	interactive_shell()
{
	print prompt;
	read_line();
	parse line;
	execute things;

}





/* do we need a while(true) loop in here? */
int main(int argc, char **argv, char **envp)
{
	t_data	*data;

	// set_signals();
	//init_minishell(data);
	//get_env_var(data);
	//show_prompt();
	if (isatty(STDIN_FILENO) == 1)
		interative_shell(data);
	else
		non_interactive(data);
	cleanup(data);
	return (data->exit_code);


}



	//init and setting up
	while (true)
	{
		//set signals
		//readline

	}
	//cleanup()
	return (status);