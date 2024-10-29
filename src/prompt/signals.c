// #include "lexer.h"
// #include "parser.h"
// #include "minishell.h"

// extern volatile sig_atomic_t g_signal_received = 0;
// // or int *g_signal_received ?
// // do i need to init?
// // to save the exit status for ctl c instead of exiting child

// // handle terminal signals
// void handle_terminal_signals()
// {
//     struct sigaction sa;
//     sa.sa_handler = sigint_handler;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;
//     sigaction(SIGINT, &sa, NULL);
// }



// // signal handler for SIGINT
// void sigint_handler()
// {
//     if (global_data)
//     {
//         reset_terminal_attributes(global_data);
//         write(STDOUT_FILENO, "\n", 1);
//         //rl_replace_line("", 0);
//         rl_on_new_line();
//         rl_redisplay();
//     }
// }


// void sigint_handler(int signum)
// {
//     (void)signum; // suppress warning
//     if (global_data)
//     {
//         // Reset terminal attributes if necessary
//         // reset_terminal_attributes(global_data);
//         write(STDOUT_FILENO, "\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
// }


// void sigquit_handler(int signum)
// {
//     (void)signum;
//     // custom behavior for SIGQUIT ?
// }

// void    signal_handlers()
// {
//     signal(SIGINT, sigint_handler);
//     signal(SIGQUIT, sigquit_handler);

// }