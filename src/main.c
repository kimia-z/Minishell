/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:09:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 12:52:25 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

/* 
-1 for failure: envp doesnt exist - malloc error
0 for success: envp added - t_env created - hstory file opened
*/
int	init_minishell(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	if (get_env(data, envp) == -1)
	{
		write_stderr("Setting up envp failed");
		return (-1);
	}
	if (load_history(&data->history, HISTORY_FILE) == -1)
	{
		write_stderr("Loading history faield");
		return (cleanup_memory_alloc(data), -1);
	}
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
			return (end_shell(&data), data.exit_status);
		if (process_cmdline(&data, input) == -1)
		{
			if (input)
				free(input);
			continue ;
		}
		if (input)
			free(input);
	}
	end_shell(&data);
	return (data.exit_status);
}
