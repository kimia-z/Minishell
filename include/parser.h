#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"


/************************************************************/
/*  Structs */

typedef enum e_rule
{
    command,
    pipeline,
    redirection,
    subshell,
    file,
} rule;

/* nodes on the tree */
typedef struct s_node
{
	rule			rule;//what rule to follow command/pipe
	char			**args ;// does command have args
	char			*path;
	int				fds[2];
	struct s_node	*right;
	struct s_node	*left;
	//s_list *redirects; //something to handle redirects?? how?
}			t_node;


/************************************************************/
/* Syntax Check */
int			syntax_checker(t_tokenlist *tokenlist);


/* Parser Functions */
void		parser(t_tokenlist *tokenlist);
// t_node *parse(t_tokenlist *tokenlist);
t_node		*parse_pipeline(t_tokenlist *tokenlist, t_node *root);
// int parse_redirection(t_tokenlist *tokenlist);
// int parse_command(t_tokenlist *tokenlist);
// t_node *parse_arguments(t_tokenlist *tokenlist);


// char *get_filename(t_tokenlist *tokenlist);


/* Parser Utils */
bool	is_pipeline(t_tokenlist *tokenlist);
bool	is_redirection(t_tokenlist *tokenlist);
bool	is_command(t_tokenlist *tokenlist);

/* Node Functions */
t_node		*add_node(rule rule);


#endif


