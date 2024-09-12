/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 16:47:59 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/09/12 18:02:16 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"


/************************************************************/
/*  Structs */

// typedef enum e_rule
// {
//     command,
//     pipeline,
//     redirection,
//     subshell,
//     file,
// } rule;

/* nodes on the tree */
// typedef struct s_node
// {
// 	rule			rule;//what rule to follow command/pipe
// 	char			**args;// does command have args
// 	char			*path;
// 	int				fds[2];
// 	struct s_node	*right;
// 	struct s_node	*left;
// 	//s_list *redirects; //something to handle redirects?? how?
// }			t_node;


typedef struct s_command
{
	char				*command;
	char				**args;
	char				*redirect_in;
	char				*redirect_out;
	char 				*redirect_append;
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

// // t_node *parse(t_tokenlist *tokenlist);
// t_node		*parse_pipeline(t_tokenlist *tokenlist, t_node *root);
// // int parse_redirection(t_tokenlist *tokenlist);
// // int parse_command(t_tokenlist *tokenlist);
// // t_node *parse_arguments(t_tokenlist *tokenlist);


// // char *get_filename(t_tokenlist *tokenlist);


/* Parser Utils */
bool			is_redirection(enum e_token_type type);
bool			is_command(enum e_token_type type);
bool			is_pipe(enum e_token_type type);


// /* Node Functions */
// t_node		*add_node(rule rule);

/* Cleanup */
void			free_command_list(t_command *cmdlist);
void			free_command(t_command *command);

#endif

