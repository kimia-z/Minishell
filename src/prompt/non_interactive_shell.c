// #include "lexer.h"
// #include "parser.h"
// #include "minishell.h"

// // void non_interactive()
// // {
// //     printf("bip bppp\n");
// // }

// /*
//     *buffer or **buffer ? - experiment
// */
// int read_line(char **buffer, size_t size)
// {
//     ssize_t bytes_read;
//     bytes_read = read(STDIN_FILENO, buffer, size - 1);
//     if (bytes_read == -1)
//     {
//         printf("error\n");
//         return (-1);
//     }
//     (*buffer)[bytes_read] = '\0';
//     return (0);
// }

// /*
// read commands from stdin until EOF
// */

// // buffer_size()
// // {

// // }



// int non_interactive()
// {
//     struct stat st;
//     size_t  size;
//     char    *line;

//     line = NULL;
//     if (fstat(STDIN_FILENO, &st) == -1)
//     {
//         printf("error\n");
//         return (-1);
//     }
//     size = st.st_size + 1;
//     line = malloc(size);
//     if (!line)
//     {
//         perror("error\n");
//         return (-1);
//     }
//     while (1)
//     {
//         if (read_line(&line, size) == -1)
//             break ;
//         //process_commandline(data, line);
//     }
//     free(line);
//     return (0);
// }


