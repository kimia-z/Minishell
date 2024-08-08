// #include "parser.h"


// /* main parsing logic */
// t_node *parse(t_tokenlist *tokenlist)
// {
//     t_node *tree;
//     tree = NULL;
//     // decide what gets to be the root ndoe
//     if (is_pipeline(tokenlist))
//     {
//         tree = parse_pipeline(tokenlist);

//     }
//     else if (is_redirection(tokenlist))
//     {
//         tree = parse_redirection(tokenlist);

//     }
//     //else if subshell
//     else if (is_command(tokenlist))
//     {
//         tree = parse_command(tokenlist);
//     }
//     return tree;

// }


// /* a temporary function to test the parsing routine */
// void    parser(t_tokenlist *tokenlist)
// {
//     t_node *tree;
//     print_token_list(tokenlist->head);
//     // receive token list from lexer
//     //call parse function and add successful nodes into a tree
//     tree= parse(tokenlist);
//     if (tree == NULL)
//     {
//         ; // 
//     }
//     else if (tree)
//     {
//         printf("tree created.\n");
//         // do semantic check
//     }
//     // free
   
// }

