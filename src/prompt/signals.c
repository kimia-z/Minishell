/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 16:36:12 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/30 17:31:49 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//NOTES
// or int *g_signal_received ? or volatile? or atomic ? or both
// do i need to init?
// to save the exit status for ctl c instead of exiting child


// handle terminal signals
// void handle_terminal_signals()
// {
//     struct sigaction sa;
//     sa.sa_handler = sigint_handler;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;
//     sigaction(SIGINT, &sa, NULL);
// }



int	*g_exit_status;



void	unset_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_for_kids(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_int_handler(int sig)
{
	(void)sig;
	*g_exit_status = ERROR_CTRL_C_;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
    // write(STDOUT_FILENO, "\n", 1);
    // write(STDOUT_FILENO, "\033[2K", 4); // Clear the entire line
    // write(STDOUT_FILENO, "\033[0G", 4); // Move cursor to the beginning of the line
    // write(STDOUT_FILENO, "minishell$ ", 11); // Print the prompt (adjust as needed)
    // fflush(stdout); // Ensure the output is flushed
}

void	set_signals(t_data *data)
{
	g_exit_status = &data->exit_status;
	signal(SIGINT, &signal_int_handler);
	signal(SIGQUIT, SIG_IGN);
}

// void signal_handlers(const char *context)
// {
//     if (strcmp(context, "interactive") == 0)
//     {
//         // Interactive shell
//         signal(SIGINT, sigint_handler);  // Handle Ctrl+C
//         signal(SIGQUIT, sigquit_handler); // Handle Ctrl+ slash
//     } else if (strcmp(context, "non_interactive") == 0)
//     {
//         signal(SIGINT, SIG_IGN);  // Ignore Ctrl+C
//         signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+ slash
//     } else if (strcmp(context, "child") == 0)
//     {
//         // Child process
//         signal(SIGINT, SIG_DFL);  // Default behavior for Ctrl+C
//         signal(SIGQUIT, SIG_DFL); // Default behavior for Ctrl+ slash
//     } else if (strcmp(context, "parent") == 0)
//     {
//         // Parent process
//         signal(SIGCHLD, SIG_IGN); // Ignore SIGCHLD to prevent zombie processes
//     }
// }