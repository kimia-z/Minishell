/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 17:49:42 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/24 21:34:53 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"

// line 183
// static void advance_token(t_parser *parser)
// {
// 	if (parser->current_token != NULL)
// 		parser->current_token = parser->current_token->next;
// }


// yea? also open the thing? - ORIGINAL
// void parse_redirection(t_command *command, t_parser *parser)
// {
// 	if (parser->current_token->type == TOKEN_OP_REDIRECTION_APPEND)
// 	{
// 		advance_token(parser);
// 		if (parser->current_token && is_command(parser->current_token->type))
// 		{
// 			command->redirect_append = ft_strdup(parser->current_token->value);
// 			printf("redirect append: %s\n", command->redirect_append);
// 		}
// 	}
// 	else if (parser->current_token->type == TOKEN_OP_REDIRECTION_OUT)
// 	{
// 		advance_token(parser);
// 		if (parser->current_token && is_command(parser->current_token->type))
// 		{
// 			command->redirect_out = ft_strdup(parser->current_token->value);
// 			printf("redirect out: %s\n", command->redirect_out);
// 		}
// 	}
// 	else if (parser->current_token->type == TOKEN_OP_REDIRECTION_IN)
// 	{
// 		advance_token(parser);
// 		if (parser->current_token && is_command(parser->current_token->type))
// 		{
// 			command->redirect_in = ft_strdup(parser->current_token->value);
// 			printf("redirect in: %s\n", command->redirect_out);
// 		}
// 	}
// }



// is there a difference whether in/append/out comes first?
void parse_redirection(t_command *command, t_token **current_token)
{
	if ((*current_token)->type == TOKEN_OP_REDIRECTION_APPEND)
	{
		//advance_token(parser);
		*current_token = (*current_token)->next;
		if (*current_token && is_command((*current_token)->type))
		{
			command->redirect_append = ft_strdup((*current_token)->value); // dont need append - just out
			printf("redirect append: %s\n", command->redirect_append);
			//command->outfile_fd = open(command->redirect_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
            //if (command->outfile_fd == -1)
               //perror("open");
		}
	}
	else if ((*current_token)->type == TOKEN_OP_REDIRECTION_OUT)
	{
		*current_token = (*current_token)->next;
		//advance_token(parser);
		if (*current_token && is_command((*current_token)->type))
		{
			command->redirect_out = ft_strdup((*current_token)->value);
			printf("redirect out: %s\n", command->redirect_out);
			//command->outfile_fd = open(command->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            //if (command->outfile_fd == -1)
                //perror("open");
		}
	}
	else if ((*current_token)->type == TOKEN_OP_REDIRECTION_IN)
	{
		*current_token = (*current_token)->next;
		//advance_token(parser);
		if (*current_token && is_command((*current_token)->type)) // is_command is unnecessary
		{
			command->redirect_in = ft_strdup((*current_token)->value);
			printf("redirect in: %s\n", command->redirect_out);
			//command->infile_fd = open(command->redirect_in, O_RDONLY);
            //if (command->infile_fd == -1)
                //perror("open");
		}
	}
}

// int	count_words(t_parser *token)
// {
// 	t_parser *temp;
// 	int		count;

// 	temp = token;
// 	count = 0;
// 	while (temp->current_token != NULL && temp->current_token->type != TOKEN_OP_PIPE)
// 	{
// 		if (temp->current_token->type != TOKEN_WORD)
// 		{
// 			temp->current_token = temp->current_token->next;
// 		}
// 		else
// 		{
// 			count++;
// 		}
// 		temp->current_token = temp->current_token->next;
// 	}
// 	if (temp->current_token->value == NULL)
// 		printf("\n\n\n nulllll \n\n");
// 	return (count);
// }

//ORIGINAL
// t_command	*parse_command(t_parser *parser)
// {
//     t_command *command;
// 	t_token *current_token;
//     int is_first_arg = 1;
//     int command_count = 0;


//     command = malloc(sizeof(t_command));
//     if (command == NULL)
//         return NULL;

//     command->command = NULL;
//     command->path = NULL;
//     command->redirect_in = NULL;
//     command->redirect_out = NULL;
//     command->redirect_append = NULL;
//     command->infile_fd = -1;
//     command->outfile_fd = -1;
//     command->next = NULL;

//     while (parser->current_token != NULL && parser->current_token->type != TOKEN_OP_PIPE)
//     {
//         printf("Parsing token: %s\n", parser->current_token->value); // Debug statement
//         if (is_command(parser->current_token->type))
//         {
//             if (is_first_arg)
//             {
//                 command->command = malloc(2 * sizeof(char *));
//                 if (command->command == NULL)
//                 {
//                     free(command);
//                     return NULL;
//                 }
//                 command->command[0] = ft_strdup(parser->current_token->value);
//                 command->command[1] = NULL;
//                 printf("Command: %s\n", command->command[0]); // Debug statement

//                 // Find command path
//                 command->path = find_command_path(command->command[0]);
//                 if (command->path == NULL)
//                 {
//                     free(command->command[0]);
//                     free(command->command);
//                     free(command);
//                     //ft_perror("path_error");
//                     return NULL;
//                 }
//                 printf("Command path: %s\n", command->path); // Debug statement

//                 is_first_arg = 0;
//                 command_count = 1;
//             }
//             else
//             {
//                 command->command = realloc(command->command, (command_count + 2) * sizeof(char *));
//                 if (command->command == NULL)
//                 {
//                     free(command->command[0]);
//                     free(command->path);
//                     free(command);
//                     return NULL;
//                 }
// 				command->command[command_count] = ft_strdup(parser->current_token->value);
// 				printf("Command in the loop: %s\n", command->command[command_count]); // Debug statement
//                 command->command[command_count + 1] = NULL;
//                 command_count++;
//             }
//         }
//         if (is_redirection(parser->current_token->type))
//             parse_redirection(command, parser);
//         advance_token(parser);
//     }
//     return command;
// }


// t_parser	*parser_init(t_tokenlist *tokenlist)
// {
// 	t_parser	*parser;

// 	parser = malloc(sizeof(t_parser));
// 	if (!parser)
// 		return (NULL);
// 	parser->tokenlist = tokenlist;
// 	parser->current_token = tokenlist->head;
// 	return (parser);
// }


// ORIGINAL
// t_command	*parse(t_parser *parser, t_tokenlist *tokenlist)
// {
// 	t_command *commandlist;
// 	t_command *last_command;
// 	t_command *current_command;

// 	commandlist = NULL;
// 	last_command = NULL;

// 	while (parser->current_token != NULL)
// 	{
// 		current_command = parse_command(parser);
// 		if (!current_command)
// 		{
// 			return (NULL); // lethal
// 		}
// 		if (!commandlist)
// 			commandlist = current_command;
// 		else
// 			last_command->next = current_command;
// 		last_command = current_command;
// 		if (parser->current_token && is_pipe(parser->current_token->type))
// 			advance_token(parser);
// 	}
// 	return (commandlist);
// }



// t_cmdlist	*parser(t_tokenlist *tokenlist)
// {
// 	t_command *commandlist;
// 	t_command *last_command;
// 	t_command *current_command;
	
// 	t_token *current_token;

// 	commandlist = NULL;
// 	last_command = NULL;

// 	current_token = tokenlist->head;


// 	while (current_token != NULL)
// 	{
// 		current_command = parse_command(parser);
// 		if (!current_command)
// 		{
// 			return (NULL); // lethal
// 		}
// 		if (!commandlist)
// 			commandlist = current_command;
// 		else
// 			last_command->next = current_command;
// 		last_command = current_command;
// 		if (current_token && is_pipe(current_token->type))
// 			advance_token(parser);
// 	}
// 	return (commandlist);
// }


t_command	*parse_command(t_token **current_token)
{
    t_command *command;
	//t_token *current_token;
    int is_first_arg = 1;
    int command_count = 0;

	//current_token = tokenlist->head;
    command = malloc(sizeof(t_command));
    if (command == NULL)
        return NULL;
    command->command = NULL;
    command->path = NULL;
    command->redirect_in = NULL;
    command->redirect_out = NULL;
    command->redirect_append = NULL;
    command->infile_fd = -1;
    command->outfile_fd = -1;
    command->next = NULL;

    while (*current_token != NULL && (*current_token)->type != TOKEN_OP_PIPE)
    {
       // printf("Parsing token: %s\n", current_token->value); // Debug statement
        if (is_command((*current_token)->type))
        {
            if (is_first_arg)
            {
                command->command = malloc(2 * sizeof(char *));
                if (!command->command)
                {
                    //free(command);
                    return NULL;
                }
                command->command[0] = ft_strdup((*current_token)->value);
                command->command[1] = NULL;
                //printf("Command: %s\n", command->command[0]); // Debug statement

                // Find command path
                command->path = find_command_path(command->command[0]);
                if (command->path == NULL)
                {

                    free(command->command[0]);
                    free(command->command);
                    free(command);
            
                    return NULL;
                }
                printf("Command path: %s\n", command->path); // Debug statement

                is_first_arg = 0;
                command_count = 1; // comment out?
            }
            else
            {
				//command_count++;
                command->command = realloc(command->command, (command_count + 2) * sizeof(char *));
                if (command->command == NULL)
                {
                    free(command->command[0]);
                    free(command->path);
                    free(command);
                    return NULL;
                }
				command->command[command_count] = ft_strdup((*current_token)->value);
				printf("Command in the loop: %s\n", command->command[command_count]); // Debug statement
                command->command[command_count + 1] = NULL;
                command_count++;
            }
        }
        if (is_redirection((*current_token)->type))
            parse_redirection(command, current_token);
        //advance_token(parser);
		*current_token = (*current_token)->next;
    }
    return command;
}

