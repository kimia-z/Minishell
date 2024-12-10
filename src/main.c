/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:09:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/10 17:06:03 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//TODO
// add appropriate exit codes
// malloc for t_history or not?? 

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
	ft_bzero(data, sizeof(t_data));

	if (get_env(data, envp) == -1)
		return (-1);
	if (load_history(&data->history, HISTORY_FILE) == -1)
		return (cleanup_memory_alloc(data), -1); // is it cleanning up history properly?
	return (SUCCESS);
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
