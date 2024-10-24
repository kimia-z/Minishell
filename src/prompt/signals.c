#include "lexer.h"
#include "parser.h"
#include "minishell.h"

#include <signal.h>


// handle terminal signals
void handle_terminal_signals()
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}



// signal handler for SIGINT
void sigint_handler()
{
    if (global_data)
    {
        reset_terminal_attributes(global_data);
        write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}
