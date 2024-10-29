/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interactive_shell.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:33:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 14:14:57 by yasamankari   ########   odam.nl         */
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

//NOTES
// do i display prompt with readline, or on STDOUT?
// could also add support for arrows and cursor



char	*get_prompt()
{
	char	*cwd;
	char	*hostname;
	char	*prompt;

	cwd = get_current_working_directory();
	hostname = get_hostname();
	prompt = build_prompt(hostname, cwd);
	free(cwd);
	free(hostname);
	return (prompt);
}


void	do_things(t_data *data)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		if (input)
		{
			if (strcmp(input, "exit") == 0)
			{
				free(input);
				break;
			}
			add_history(input);
			add_history_node(&data->terminal.history, input);
			process_commandline(data, input); //main logic
			free(input);
		}
		else
			write(STDOUT_FILENO, "No input provided.\n", 19);
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
	do_things(data);
}