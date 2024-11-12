/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:09:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/12 20:40:27 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//TODO
// implement signal handler - check if working
// change the way you check for interactive shell - 

// NOTES
// the data strcut : does it need to be static? 


int	init_minishell(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data)); // set everything to 0 or null
	//reset/flush terminal if necessary ?
	//read_history_file(); // open history file and read contents
	// search for path here?
	if (get_env(data, envp) == -1)// error check
		return (-1);
	if (load_history(&data->history, HISTORY_FILE) == -1)
		printf("too bad\n"); // error check - what happens if loading history fails?
	return (0);
}

// void	shell_mode(t_data *data)
// {
// 	if (isatty(STDIN_FILENO))
// 		return (interactive_shell(data));
// 	else
// 		return ;
// }


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;


	(void)argc;
	(void)argv;

	if (init_minishell(&data, envp) == -1)
		return (-1);
	while (1)
	{
		set_signals(&data); // have different modes
		input = get_commandline(&data);
		if (input == NULL)
			//cleanup
		if (parser(&data, input) == -1) // dont print , just handle exit, cleanup
			return (1); // 
	}
	//exit_shell(&data, "copying env failed."); //what resources do we need to free/cleanup at this point?
	//shell_mode(&data);


	save_history(&data.history, HISTORY_FILE);
	
	free_history(&data.history);
	clear_history(); // ? rl_ ?
	rl_free_line_state();
	rl_cleanup_after_signal();
	
	do_things(&data);
	
	end_shell(&data);
	return (data.exit_status);
}