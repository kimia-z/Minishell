/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:58:32 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/26 17:30:47 by ykarimi       ########   odam.nl         */
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
#define PROMPT_DEFAULT "minishell> "

// file to save history 
#define HISTORY_FILE ".minishell_history"

# define SUCCESS 0 
# define ERROR_GENERIC 1
# define ERROR_BUILTIN_IMPROPER 2
# define ERROR_CANT_EXEC 126
# define ERROR_CMD_NOT_FOUND 127
# define FATAL_ERROR_SIG 128
# define ERROR_CTRL_C_ 130

/* max commands kept in history */
# ifndef HISTORY_MAX
#  define HISTORY_MAX 100
# endif

extern int	g_exit_code;

/************************************************************/
/*  Structs */

typedef enum e_sig
{
	PARENT,
	CHILD,
	HERE_DOC,
	IGNORE,
	MINISHELL
}		t_sig;

typedef struct s_historynode
{
	char					*command;
	struct s_historynode	*next;
}				t_historynode;

typedef struct s_history
{
	t_historynode	*head;
	t_historynode	*tail;
	int				size;
}			t_history;

typedef enum e_errtype
{
	success = 0,
	malloc_error,
	syscall_error,
	cmd_error,
	permission_error,
	syntax_error,
	path_error,
	envp_error,
	generic_error
	
}			t_errtype;

// define what kind of errors you wanna specify(keywords)
typedef struct s_error
{
	t_errtype	errortype;
	char 		*error_msg;
}			t_error;


typedef enum s_processtype
{
	builtin,
	command,
	error
}				t_processtype;

// typedef struct s_process
// {
// 	t_processtype	process_type;
// 	int				pid;
// 	int				status;
// }			t_process;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

/* more things need to be added as we go */
typedef struct s_data
{
	t_env			*env;
	t_error			error;
	t_history		history;
	t_cmdlist		*commands;
	char			**envp;
	int				signal;
	int				exit_status;
}					t_data;
				
/************************************************************/
/* Setup functions */
int			init_minishell(t_data *data,  char **envp);
char		*get_prompt();
char		*get_commandline(t_data *data);
int			process_cmdline(t_data *data, char *input);
void		exit_code(int code);

/* Envp functions */
int			get_env(t_data *data, char **envp);
int			add_env_to_data(t_data *data, char **envp);
void		free_env_list(t_env *env_list);

/* Signal functions */
void		parent_sig_handler(int sig);
void		heredoc_sig_handler(int sig);
int			signal_mode(int mode);

/* history functions */
int			load_history(t_history *history, const char *filename);
int			add_history_node(t_history *history, const char *command);
void		free_history(t_history *history);
int			save_history(t_history *history, const char *filename);
void		trim_newline(char *str);

/* Parsing */
t_tokenlist	*tokenizer(char **envp, char *input);



/* Error Handling */
void	free_2d(void ***thing);
void	free_nullify(void **thing);
void	cleanup_memory_alloc(t_data *data);
void	write_stderr(char *errmsg);
void	end_shell(t_data *data);
// void    ft_perror(char *msg);
// void	exit_error(int exit_status, char *msg);
//void	reset_terminal(t_data *data);
//void	exit_shell(t_data *data, char *err_msg);
// void	exit_error(int exit_status, char *msg);
// void	ft_perror(t_errtype);
//void clear_screen();


/* Utils */
//void print_command_list(t_command *cmdlist);
// add more printing and testing functions
void print_envp(char **envp);
void print_env_list(t_env *env_list);
void print_command(t_command *command);
void print_command_list(t_cmdlist *commandlist);





#endif

