/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 16:47:59 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/10/30 18:17:39 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

/************************************************************/
/*  Structs */

typedef struct s_command
{
	//char	**command;
	char				*command;//remove
	char				*path;
	char				**args; //remove
	char				*redirect_in;
	char				*redirect_out;
	char 				*redirect_append;
	//int in_fd
	//int out_fd
	struct s_command	*next;
}				t_command;


typedef struct s_parser
{
	t_tokenlist			*tokenlist;
	t_token				*current_token;
}				t_parser;


/************************************************************/
/* Syntax Check */
int				syntax_checker(t_tokenlist *tokenlist);

/* Parser Functions */
t_command		*parse(t_parser *parser, t_tokenlist *tokenlist);
t_parser		*parser_init(t_tokenlist *tokenlist);
t_command		*parse_command(t_parser *parser);
void			parse_redirection(t_command *command, t_parser *parser);
int				get_arg(t_command *command, char *value);

/* Command Path */
char			*find_command_path(char *commandname);

/* Parser Utils */
bool			is_redirection(enum e_token_type type);
bool			is_command(enum e_token_type type);
bool			is_pipe(enum e_token_type type);

/* Cleanup */
void			free_command_list(t_command *cmdlist);
void			free_command(t_command *command);

#endif

