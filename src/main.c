/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:09:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 12:45:17 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void	init_minishell(t_data *data)
{
	memset(data, 0, sizeof(t_data)); // set everything to 0 or null
	//init fds if you wish to keep them in t_data struct
	//reset/flush terminal if necessary ?
}


/*
	do we need a while(true) loop in here? 
	interative -> input from a terminal 
	non-interative input from a file or pipe
*/
// data: does it need to be static? 
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	//signal_handlers();sigint - sigquit - sigwinch
	init_minishell(&data);
	if (get_env(&data, envp) == -1)
		exit_shell(&data, "copying env failed."); //what resources do we need to free/cleanup at this point?
	if (isatty(STDIN_FILENO) == 1) //if input is from a terminal
		interactive_shell(&data); //termcap lib - prompt
	else
		non_interactive(); // implement ways to invoke this - now all goes to interactive
	end_shell(&data);
	return (data.exit_status);
}
