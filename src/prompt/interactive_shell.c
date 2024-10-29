/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interactive_shell.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:33:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 21:08:41 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include <readline/readline.h>

//TODO
// for interative_shell, define what happens when error
// change the namne of do_things()
// ctl c doesnt work for termination in do_things
// implement ft_strcmp in libft
//check functions for errors
// check return values
// implement handle_buffer()


//NOTES
// do i display prompt with readline, or on STDOUT?
// could also add support for arrows and cursor



// handle_buffer()
// {
// 	if newline
// 		flush line;
// 	if ctrl c
// 	{
// 		update exit status;
// 		print ^C to prompt;
// 		cleanup if necessary;
// 	}
// }

void	do_things(t_data *data)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt); //include error checking
		free(prompt);
		if (input)
		{
			if (strcmp(input, "exit") == 0) //also add ctrl d or empty 
			{
				free(input);
				break;
			}
			add_history(input);
			add_history_node(&data->terminal.history, input);
			//process_commandline(data, input); //main logic
			parser(data, input);
			free(input);
			//handle_buffer();
		}
		//else
			//write(STDOUT_FILENO, "No input provided.\n", 19);
	}
	save_history(&data->terminal.history, HISTORY_FILE);
	free_history(&data->terminal.history);
	clear_history(); // ? rl_ ?
	rl_free_line_state();
	rl_cleanup_after_signal();
}

/* 
show prompt outside of while loop or inside ?
*/
void	interactive_shell(t_data *data)
{
	initialize_termcap();
	set_terminal_attributes(data);
	ft_bzero(&data->terminal.history, sizeof(t_history));
	if (load_history(&data->terminal.history, HISTORY_FILE) == -1)
		printf("too bad\n");
	//do_things(data);
	// add cursor functions
}