/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:58:32 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/23 14:31:33 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "libft"
# include "lexer.h"
# include "parser.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <pwd.h>
# include <sys/types.h>
# include <errno.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>

/* Macros for color codes */
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"
# define PROMPT_DEFAULT "minishell> "

/* file to save history */
# define HISTORY_FILE ".minishell_history"

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

typedef struct s_cmdlist	t_cmdlist;

typedef enum e_sig
{
	PARENT,
	CHILD,
	HERE_DOC,
	IGNORE,
	MINISHELL
}							t_sig;

typedef struct s_historynode
{
	char					*command;
	struct s_historynode	*next;
}							t_historynode;

typedef struct s_history
{
	t_historynode	*head;
	t_historynode	*tail;
	int				size;
}							t_history;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}							t_env;

typedef struct s_data
{
	t_env			*env;
	t_history		history;
	t_cmdlist		*commands;
	char			**envp;
	int				signal;
	int				exit_status;
}							t_data;

/************************************************************/
/* Setup functions */

int			init_minishell(t_data *data, char **envp);
char		*get_prompt(void);
char		*get_commandline(t_data *data);
int			process_cmdline(t_data *data, char *input);
char		*space_putter(char *input);
t_tokenlist	*tokenize_input(t_data *data, char *input);
void		trim_quotes_from_tokenlist(t_tokenlist *tokenlist);
void		trim_quotes_from_token(char **value);
void		process_quotes(char **value, char *quote_start, char *quote_end);

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

/* Parsing */
t_tokenlist	*tokenizer(char **envp, char *input);

/* Error Handling */
void		free_2d(void ***thing);
void		free_nullify(void **thing);
void		cleanup_memory_alloc(t_data *data);
void		write_stderr(char *errmsg);
void		end_shell(t_data *data);

#endif
