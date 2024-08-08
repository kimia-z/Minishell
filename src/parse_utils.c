// #include "parser.h"


// t_node *parse_pipeline(t_tokenlist *tokenlist)
// {
//     t_node *root;
//     t_node *left;
//     t_node *right;
//     t_node *redirect;

//     root = create_node(pipe, );
//     root->left = parse_command(); // get the first command
//     root->right = parse_comamnd(); // get the second command
//     if (is_redirection(tokenlist))
//     {
//         redirect = create_node(redirection, );
//         redirect->left = root->left;
//         redirect->right = create_node(file, get_filename(tokenlist));
//         root->right = redirect->right;


//     }
    

// }



// t_node *parse_redirection(t_tokenlist *tokenlist)
// {
//     t_node *root;
//     t_node *right;
//     t_node *left;
//     root = create_node(redirection, NULL);
//     root->left = parse_command(tokenlist);
//     root->right = create_node(file, get_filename(tokenlist));
// }

// t_node *parse_command(t_tokenlist *tokenlsit)
// {
//     is_command()
//         printf("no command");
//     parse_arguments();

// }

// t_node *parse_arguments(t_tokenlist *tokenlist)
// {

// }



// int is_pipeline(t_tokenlist *tokenlist)
// {

// }
// int is_redirection(t_tokenlist *tokenlist)
// {

// }

// int is_command(t_tokenlist *tokenlist)
// {

// }