#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// get the current working directory
static char *get_current_working_directory()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
        perror("getcwd");
        return strdup("minishell> ");
    }
    return strdup(cwd);
}

// get the hostname
static char *get_hostname()
{
    char hostname[1024];
    if (gethostname(hostname, sizeof(hostname)) != 0)
	{
        perror("gethostname");
        return strdup("minishell> ");
    }
    return strdup(hostname);
}


static char *build_prompt(const char *hostname, const char *cwd)
{
    char *prompt;
	
	prompt = malloc(strlen(GREEN) + strlen(hostname) + strlen(RESET) +
                          strlen(":") + strlen(BLUE) + strlen(cwd) + strlen(RESET) +
                          strlen("$ ") + 1);
    if (prompt == NULL)
	{
        perror("malloc");
        return strdup("minishell> ");
    }
    strcpy(prompt, GREEN);
    strcat(prompt, hostname);
    strcat(prompt, RESET);
    strcat(prompt, ":");
    strcat(prompt, BLUE);
    strcat(prompt, cwd);
    strcat(prompt, RESET);
    strcat(prompt, "$ ");
    return prompt;
}


// Function to get the current working directory and format the prompt
char *get_prompt()
{
    char *cwd;
    char *hostname;
    char *prompt;

	cwd = get_current_working_directory();
	hostname = get_hostname();
	prompt = build_prompt(hostname, cwd);
    free(cwd);
    free(hostname);
    return prompt;
}



/*
    print prompt - getcwd - getlogin - gethostname
    read line
    parse line
    execute things
*/

// note: ctl c doesnt work for termination
void interactive_shell(t_data *data)
{
    char *input;
    char *prompt;

    initialize_termcap();
    set_terminal_attributes(data);
    handle_terminal_signals(data);

    // Load history from file into linked list and Readline
    load_history(&data->history, HISTORY_FILE);

    while (1)
	{
        prompt = get_prompt();
        input = readline(prompt);
        free(prompt);
        if (input)
		{
            if (strcmp(input, "exit") == 0)
			{
                free(input);
                break;
            }
            add_history(input);
            // add input to history linked list
            add_history_node(&data->history, input);
            process_commandline(input);
            free(input);
        }
		else
		{
            write(STDOUT_FILENO, "No input provided.\n", 19);
        }
    }

    // Save history to file
    save_history(&data->history, HISTORY_FILE);
    free_history(&data->history);
    reset_terminal_attributes(data);
    rl_clear_history();
    rl_free_line_state();
    rl_cleanup_after_signal();
}