#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"


/************************************************************/
/*  Structs */

/* nodes on the tree */
// typedef struct s_node
// {
// 	what rule to follow command/pipe
// 	**args // does command have args
// 	*exec path
// 	fds[2]
// 	s_list *redirects
// 	struct s_node *right_node;
// 	struct s_node *left_node;
// }			t_node;





/************************************************************/

void    parser(t_tokenlist *tokenlist);
// t_node	add_node();
// t_node	create_tree(t_tokenlist *tokens);
// int	syntax_check();

#endif


