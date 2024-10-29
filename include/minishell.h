/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:58:32 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 13:56:33 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


#include "lexer.h"
#include "parser.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
#include <errno.h>
#include <termcap.h>
#include <termios.h>
#include <signal.h>


// Macros for color codes
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

// file to save history 
#define HISTORY_FILE ".minishell_history"

# define SUCCESS 0 
# define ERROR_GENERIC 1
# define ERROR_BUILTIN_IMPROPER 2
# define ERROR_CANT_EXEC 126
# define ERROR_CMD_NOT_FOUND 127
# define FATAL_ERROR_SIG 128
# define ERROR_CTRL_C_ 130

// max commands kept in history
# ifndef HISTORY_MAX
#  define HISTORY_MAX 1000
# endif


typedef struct s_historynode
{
	char					*command;
	struct s_historynode	*next;
}				t_historynode;

typedef struct s_history
{
	t_historynode	*head;
	t_historynode	*tail;
}			t_history;

// define what kind of errors you wanna specify(keywords)
typedef struct s_error
{
	int		error_num;
	char 	*error_msg;
}			t_error;


typedef enum s_processtype
{
	builtin,
	command,
	error
}				t_processtype;


typedef struct s_process
{
	t_processtype	process_type;
	int				pid;
	int				status;
}			t_process;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_terminal
{
	struct termios	original;
	struct termios	modified;
	t_history		history;
	bool			is_modified;
}					t_terminal;

/* more things need to be added as we go */
typedef struct s_data
{
	t_lexer			*lexer;
	t_token			*tokenlist;
	t_parser		*parser;
	t_command		*cmdlist;
	t_env			*env;
	t_error			error;
	t_terminal		terminal;
	int				signal;
	int				exit_status;
}					t_data;



/* Utils */
void print_command_list(t_command *cmdlist);
// add more printing and testing functions

/* init functions */
void	init_minishell(t_data *data);

/* non interactive mode */
int		read_line(char **buffer, size_t size);
int		non_interactive();

/* interactive shell */
void	interactive_shell(t_data *data);
void	initialize_termcap();
void	set_terminal_attributes(t_data *data);
void	reset_terminal_attributes(t_data *data);
char	*get_prompt();
void clear_screen();
void move_cursor(int row, int col);


/* signals */
// void sigint_handler();
// void handle_terminal_signals();



/* history functions */
int		load_history(t_history *history, const char *filename);
int		add_history_node(t_history *history, const char *command);
void	free_history(t_history *history);
int		save_history(t_history *history, const char *filename);


/* Env functions */
int	get_env(t_data *data, char **envp);



/* Error Handling */
// void    ft_perror(char *msg);
// void	exit_error(int exit_status, char *msg);
void	reset_terminal(t_data *data);
void	exit_shell(t_data *data, char *err_msg);
void	end_shell(t_data *data);

#endif

