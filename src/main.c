/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:09:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/12 16:58:17 by ykarimi       ########   odam.nl         */
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


void	init_minishell(t_data *data)
{
	memset(data, 0, sizeof(t_data)); // set everything to 0 or null
	//init fds if you wish to keep them in t_data struct
	//reset/flush terminal if necessary ?
}

void	shell_mode(t_data *data)
{
	if (isatty(STDIN_FILENO))
		return (interactive_shell(data));
	else
		return ;
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;

	init_minishell(&data);
	get_env(&data, envp);
		//exit_shell(&data, "copying env failed."); //what resources do we need to free/cleanup at this point?
	shell_mode(&data);
	
	do_things(&data);
	
	end_shell(&data);
	return (data.exit_status);
}