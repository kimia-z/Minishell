/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:58:32 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/28 23:11:45 by yasamankari   ########   odam.nl         */
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

#define HISTORY_FILE ".minishell_history"



typedef struct s_historynode
{
    char                *command;
    struct s_historynode    *next;

}           t_historynode;

typedef struct s_historylist
{
    t_historynode *head;
    t_historynode *tail;
}			t_historylist;


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


/* more things need to be added as we go */
typedef struct s_data
{
	t_lexer		*lexer;
	t_token		*tokenlist;
	t_parser	*parser;
	t_command	*cmdlist;
	t_env		*env;
	t_error		error;
	int			signal;
	int			exit_status;
	t_historylist	history;
	struct termios orig_termios;
}               t_data;

static t_data *global_data; // global var for signal


/* Utils */
void print_command_list(t_command *cmdlist);

/* init functions */
void	init_minishell(t_data *data);

/* non interactive mode */
int		read_line(char **buffer, size_t size);
int	non_interactive();

/* interactive shell */
void	interactive_shell(t_data *data);
void	initialize_termcap();
void	set_terminal_attributes(t_data *data);
void	reset_terminal_attributes(t_data *data);
char	*get_prompt();
void clear_screen();
void move_cursor(int row, int col);


/* signals */
void sigint_handler();
void handle_terminal_signals();



/* history functions */
void add_history_node(t_historylist *history, const char *command);
void load_history(t_historylist *history, const char *filename);
void save_history(t_historylist *history, const char *filename);
void free_history(t_historylist *history);
void process_commandline(t_data *data, char *input);


/* Env functions */
int init_env(t_data *data, char **envp);
int add_env_node(t_env **env_list, t_env **last_node, const char *env_var);
void free_env_list(t_env *env_list);
t_env *create_env_node(const char *env_var);


#endif

