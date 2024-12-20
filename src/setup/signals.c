/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 16:36:12 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/10 23:03:10 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//NOTES
// or int *g_exit_code? or volatile? or atomic ? or both
// to save the exit status for ctl c instead of exiting child
// readline lib is annoying on mac :( try linux
// make sure things work here

int	g_exit_code;

void clear_line() {
    write(STDOUT_FILENO, "\r", 1); // Carriage return
    for (int i = 0; i < 80; i++) { // Assuming a maximum line length of 80 characters
        write(STDOUT_FILENO, " ", 1); // Overwrite with spaces
    }
    write(STDOUT_FILENO, "\r", 1); // Move the cursor back to the beginning
}

void	parent_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		exit_code(ERROR_CTRL_C_);
		write(STDOUT_FILENO, "\n", 1);
		//rl_on_new_line();
		rl_on_new_line(); // on mac
		//rl_replace_line("", 0);
		clear_line(); //on mac
		rl_redisplay();
	}
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		//rl_replace_line("", 0);
		rl_on_new_line();
		exit(ERROR_CTRL_C_);
	}
}

int	signal_mode(int mode)
{
	if (mode == MINISHELL)
	{
		if (signal(SIGINT, parent_sig_handler) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (-1);
	}
	else if (mode == CHILD)
	{
		if (signal(SIGINT, parent_sig_handler) == SIG_ERR || signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			return (-1);
	}
	else if (mode == HERE_DOC)
	{
		if (signal(SIGINT, heredoc_sig_handler) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (-1);
	}
	else if (mode == IGNORE)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (-1);
	}
	return (0);
}