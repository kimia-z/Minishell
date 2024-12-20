/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:09:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/26 18:22:30 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//TODO
// implement signal handler - check if working
// add appropriate exit codes
// malloc for t_history or not?? 

// NOTES
// the data strcut : does it need to be static? 

void	exit_code(int code)
{
	g_exit_code = code;
}


/* 
-1 for failure: envp doesnt exist - malloc error
0 for success: envp added - t_env created - hstory file opened
*/
int	init_minishell(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data)); // set everything to 0 or null
	//reset/flush terminal if necessary ?
	// search for path herea nd save it data struct?
	if (get_env(data, envp) == -1)
		return (-1); // no cleanup necessary for failure - for success envp and env list
	//ft_bzero(&data->history, sizeof(t_history)); malloc here or not??
	if (load_history(&data->history, HISTORY_FILE) == -1)
		return (cleanup_memory_alloc(data), -1); // is it cleanning up history properly?
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	(void)argc;
	(void)argv;
	if (init_minishell(&data, envp) == -1)
		return (EXIT_FAILURE);
	while (1)
	{
		if (signal_mode(MINISHELL) == -1)
			break ;
		input = get_commandline(&data);
		if (!input)
		{
			end_shell(&data); // also pass in the exit_code?
			return (EXIT_FAILURE);
		}
		if (process_cmdline(&data, input) == -1)
		{
			free(input);
			continue;
		}
		free(input);
	}
	end_shell(&data);
	return (0);
}
