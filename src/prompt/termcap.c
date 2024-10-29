/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   termcap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:13:29 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 20:21:05 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// TODO
// for initialize_termcap, choose no buffer or yes buffer, and why
// think about cursor

// reset terminal attributes - error and return ?
void reset_terminal_attributes(t_data *data)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data->terminal.original) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}


// // Function to move the cursor to a specific position
// void move_cursor(int row, int col)
// {
// 	char *move_cmd = tgetstr("cm", NULL);
// 	if (move_cmd)
// 	{
// 		tputs(tgoto(move_cmd, col, row), 1, putchar);
// 	}
// }


void clear_screen()
{
	char *clear_cmd = tgetstr("cl", NULL);
	if (clear_cmd)
	{
		tputs(clear_cmd, 1, putchar);
	}
}

/*
set terminal attributes
make sure when you're exiting there's no leaks or dangling things
check if you're good with the mentioned attr
enables echo - diasbales canonical mode
you sure about echo ?
TCSANOW vs. TCSAFLUSH - which one and why
*/ 
void	set_terminal_attributes(t_data *data)
{
	if (tcgetattr(STDIN_FILENO, &data->terminal.original) == -1)
		exit_error(ERROR_GENERIC, "tcgetattr");
	data->terminal.modified = data->terminal.original;
	data->terminal.modified.c_lflag &= ~ICANON;
	data->terminal.modified.c_lflag |= ECHO;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &data->terminal.modified) == -1)
		exit_error(ERROR_GENERIC, "tcgetattr");
	data->terminal.is_modified = true; 
}

/*
initialize termpcap
return value ?
go with buffer or internal static buffer? (null)
*/
void	initialize_termcap()
{
	char	term_buffer[2048];

	if (tgetent(term_buffer, getenv("TERM")) < 0)
		exit_error(ERROR_GENERIC, "termcap");
}