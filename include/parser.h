/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 16:47:59 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 14:04:37 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"
# define MAX_CMD_ARGS 1024

/************************************************************/
/*  Structs */
typedef struct s_data	t_data;

typedef struct s_command
{
	char				**command;
	char				*path;
	char				*redirect_in;
	char				*redirect_out;
	int					infile_fd;
	int					outfile_fd;
	bool				*is_quotes;
	struct s_command	*next;
}						t_command;

typedef struct s_cmdlist
{
	size_t			num_commands;
	t_command		*head;
}				t_cmdlist;

/************************************************************/
/* Syntax Check */
int				syntax_checker(t_tokenlist *tokenlist);

/* Parser Functions */
t_cmdlist		*parser_main(t_tokenlist *tokenlist, t_data *data);
t_command		*parse_command(t_token **current_token, t_data *data);
int				parse_redirection(t_command *command, \
								t_token **current_token);
t_cmdlist		*cmdlist_init(void);
int				parse_command_list(t_cmdlist *cmdlist, \
				t_token **current_token, t_data *data);
int				handle_first_arg(t_command *command, \
								t_token *current_token);
int				handle_subsequent_args(t_command *command, t_token \
				*current_token, int command_count);
int				handle_command_args(t_command *command, t_token \
									**current_token, int *command_count);
int				handle_redirections(t_command *command, \
									t_token **current_token);
/* Command Path */
char			*find_path(char *commandname);

/* Parser Utils */
bool			is_redirection(enum e_token_type type);
bool			is_command(enum e_token_type type);
bool			is_pipe(enum e_token_type type);

/* Cleanup */
void			free_command_list(t_cmdlist *cmdlist);
void			free_command(t_command *command);
void			free_command_resources(t_command *command, int command_count);

/* Heredoc */
int				handle_heredoc(const char *delimiter);

#endif
