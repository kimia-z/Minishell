// #ifndef PARSER_H
// # define PARSER_H

// #include "lexer.h"


/************************************************************/
/*  Structs */


// typedef enum e_rule
// {
//     command,
//     pipe,
//     redirection,
//     subshell,
//     //file,
// } rule;

// /* nodes on the tree */
// typedef struct s_node
// {
// 	rule rule;//what rule to follow command/pipe
// 	char **args ;// does command have args
// 	char *path;
// 	int fds[2];
// 	//s_list *redirects;
// 	struct s_node *right_node;
// 	struct s_node *left_node;
// }			t_node;





// /************************************************************/
// /* Parser functions */
// void    parser(t_tokenlist *tokenlist);
// t_node *parse(t_tokenlist *tokenlist);
// int parse_pipeline(t_tokenlist *tokenlist);
// int parse_redirection(t_tokenlist *tokenlist);
// int parse_command(t_tokenlist *tokenlist);
// t_node *parse_arguments(t_tokenlist *tokenlist);
// // t_node	add_node();
// // t_node	create_tree(t_tokenlist *tokens);
// // int	syntax_check();
// int is_pipeline(t_tokenlist *tokenlist);
// int is_redirection(t_tokenlist *tokenlist);
// int is_command(t_tokenlist *tokenlist);
// char *get_filename(t_tokenlist *tokenlist);

// /* Node functions */

// #endif


