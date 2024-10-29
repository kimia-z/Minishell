/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 12:41:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 14:13:50 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//TODO
// for exit_shell, include a scenario when it's not error and you wanna exit


/* Writing errors to STDERR */
void	write_stderr(char *errmsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (errmsg)
		ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void free_command(t_command *command)
{
	int i;

	if (command == NULL)
		return;

	if (command->command != NULL)
		free(command->command);

	if (command->args != NULL)
	{
		for (i = 0; command->args[i] != NULL; i++)
		{
			free(command->args[i]);
		}
		free(command->args);
	}
	if (command->redirect_in != NULL)
		free(command->redirect_in);
	if (command->redirect_out != NULL)
		free(command->redirect_out);
	if (command->redirect_append != NULL)
		free(command->redirect_append);

	free(command);
}

void free_command_list(t_command *cmdlist)
{
	t_command *current = cmdlist;
	t_command *next;

	while (current != NULL)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
}

/* prints error to stderr */
void	ft_perror(char *msg)
{
	ft_putstr_fd("-bash: ", STDERR_FILENO);
	perror(msg);
}

/* exit and print error to stderr*/
void	exit_error(int exit_status, char *msg)
{
	ft_perror(msg);
	//reset_terminal();
	exit(exit_status);
}

/* when things went well and you wanna exit */
void	end_shell(t_data *data)
{
	printf("end shell\n");
	//free all malloced
	//reset_terminal();
	//close_fds();
}

/* 
when things might have gone south and you wanna handle error and exit 
terminal settings might change when entering interactive mode(canonical mdoe and line buffered input for example)
*/
void	exit_shell(t_data *data, char *err_msg)
{
	if (err_msg)
		ft_perror(err_msg);
	reset_terminal(data);
	exit(EXIT_FAILURE);
}

/* 
reset terminal settings to original before exiting
TCSANOW or  TCSAFLUSH ? why ?
*/
void	reset_terminal(t_data *data)
{
	if (!data->terminal.is_modified)
		return ;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->terminal.original) == -1)
		ft_perror("tcsetattr");
}