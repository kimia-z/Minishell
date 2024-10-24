#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// Function to initialize termcap - return value?
void initialize_termcap()
{
    char term_buffer[2048];

    if (tgetent(term_buffer, getenv("TERM")) < 0)
    {
        write(STDERR_FILENO, "Could not access the termcap database.\n", 39);
        exit(1);
    }
}

// Function to set terminal attributes - work on erturn vlaue 
void set_terminal_attributes(t_data *data)
{
    struct termios new_termios;

    // get the current terminal attributes
    if (tcgetattr(STDIN_FILENO, &data->orig_termios) == -1)
    {
        perror("tcgetattr");
        exit(1);
    }

    // set the new terminal attributes
    new_termios = data->orig_termios;
    new_termios.c_lflag &= ~ICANON; // disable canonical mode
    new_termios.c_lflag |= ECHO;    // enable echo
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
    {
        perror("tcsetattr");
        exit(1);
    }
}

// reset terminal attributes - error and return ?
void reset_terminal_attributes(t_data *data)
{
    if (tcsetattr(STDIN_FILENO, TCSANOW, &data->orig_termios) == -1)
    {
        perror("tcsetattr");
        exit(1);
    }
}


// Function to move the cursor to a specific position
void move_cursor(int row, int col)
{
    char *move_cmd = tgetstr("cm", NULL);
    if (move_cmd)
    {
        tputs(tgoto(move_cmd, col, row), 1, putchar);
    }
}


void clear_screen()
{
    char *clear_cmd = tgetstr("cl", NULL);
    if (clear_cmd)
    {
        tputs(clear_cmd, 1, putchar);
    }
}