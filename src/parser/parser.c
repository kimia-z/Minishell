/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 17:49:42 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/12 17:12:02 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"
// line 183
static void advance_token(t_parser *parser)
{
	if (parser->current_token != NULL)
		parser->current_token = parser->current_token->next;
}


// yea? also open the thing?
void parse_redirection(t_command *command, t_parser *parser)
{
	if (parser->current_token->type == TOKEN_OP_REDIRECTION_APPEND)
	{
		advance_token(parser);
		if (parser->current_token && is_command(parser->current_token->type))
		{
			command->redirect_append = ft_strdup(parser->current_token->value);
			printf("redirect append: %s\n", command->redirect_append);
		}
	}
	else if (parser->current_token->type == TOKEN_OP_REDIRECTION_OUT)
	{
		advance_token(parser);
		if (parser->current_token && is_command(parser->current_token->type))
		{
			command->redirect_out = ft_strdup(parser->current_token->value);
			printf("redirect out: %s\n", command->redirect_out);
		}
	}
	else if (parser->current_token->type == TOKEN_OP_REDIRECTION_IN)
	{
		advance_token(parser);
		if (parser->current_token && is_command(parser->current_token->type))
		{
			command->redirect_in = ft_strdup(parser->current_token->value);
			printf("redirect in: %s\n", command->redirect_out);
		}
	}
}

// check>??
// malloc error
// int get_arg(t_command *command, char *value)
// {
// 	char	**new_args;
// 	int i = 0;
// 	int j = 0;

// 	// Count the existing arguments
// 	if (command->args != NULL)
// 	{
// 		while (command->args[i] != NULL)
// 			i++;
// 	}

// 	// Allocate memory for the new argument array
// 	new_args = malloc((i + 2) * sizeof(char *));
// 	if (new_args == NULL)
// 		return (ft_perror(malloc_error), 1); 

// 	// Copy existing arguments to the new array
// 	while (j < i)
// 	{
// 		new_args[j] = command->args[j];
// 		j++;
// 	}

// 	// Add the new argument
// 	new_args[i] = ft_strdup(value);
// 	new_args[i + 1] = NULL;

// 	// Free the old args array if it exists
// 	if (command->args != NULL)
// 		free(command->args);

// 	// Update the command's args array
// 	command->args = new_args;
// 	return (0);
// }

//double check the logic

int	count_words(t_parser *token)
{
	t_parser *temp;
	int		count;

	temp = token;
	count = 0;
	printf("\n\n\n from c word: %s\n", temp->current_token->value);
	while (temp->current_token != NULL && temp->current_token->type != TOKEN_OP_PIPE)
	{
		if (temp->current_token->type != TOKEN_WORD)
		{
			temp->current_token = temp->current_token->next;
		}
		else
		{
			count++;
		}
		temp->current_token = temp->current_token->next;
	}
	if (temp->current_token->value == NULL)
		printf("\n\n\n nulllll \n\n");
	return (count);
}


t_command	*parse_command(t_parser *parser)
{
    t_command *command;
    int is_first_arg = 1;
    int command_count = 0;

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

    while (parser->current_token != NULL && parser->current_token->type != TOKEN_OP_PIPE)
    {
        printf("Parsing token: %s\n", parser->current_token->value); // Debug statement
        if (is_command(parser->current_token->type))
        {
            if (is_first_arg)
            {
                command->command = malloc(2 * sizeof(char *));
                if (command->command == NULL)
                {
                    free(command);
                    return NULL;
                }
                command->command[0] = ft_strdup(parser->current_token->value);
                command->command[1] = NULL;
                printf("Command: %s\n", command->command[0]); // Debug statement

                // Find command path
                command->path = find_command_path(command->command[0]);
                if (command->path == NULL)
                {
                    free(command->command[0]);
                    free(command->command);
                    free(command);
                    //ft_perror("path_error");
                    return NULL;
                }
                printf("Command path: %s\n", command->path); // Debug statement

                is_first_arg = 0;
                command_count = 1;
            }
            else
            {
                command->command = realloc(command->command, (command_count + 2) * sizeof(char *));
                if (command->command == NULL)
                {
                    free(command->command[0]);
                    free(command->path);
                    free(command);
                    return NULL;
                }
				command->command[command_count] = ft_strdup(parser->current_token->value);
				printf("Command in the loop: %s\n", command->command[command_count]); // Debug statement
                command->command[command_count + 1] = NULL;
                command_count++;
            }
        }
        if (is_redirection(parser->current_token->type))
            parse_redirection(command, parser);
        advance_token(parser);
    }
    return command;
}


// malloc error - 
//test this function
// t_command	*parse_command(t_parser *parser)
// {
// 	t_command *command;
// 	int is_first_arg = 1;
// 	command = malloc(sizeof(t_command));
// 	if (command == NULL)
// 		return NULL;
	// command->command = NULL;
	// command->args = NULL;
	// command->path = NULL;
	// command->redirect_in = NULL;
	// command->redirect_out = NULL;
	// command->redirect_append = NULL;
	// command->next = NULL;

	// int i = 0;
	// //t_parser *temp = parser;
	// printf("\n\n\n curr token befor ec word: %s\n", parser->current_token->value);
	// int word_token = count_words(parser);
	// printf("word:%d\n", word_token);
	// command->command = malloc (sizeof(char *) * word_token + 1);
	// command->command[word_token] = NULL;
	// if (command->command == NULL)
	// 	return NULL;
	// printf("\n\nhello out of while\n\n");
	// printf("\n\n\n curr token: %s\n", parser->current_token->value);
	// printf("\n\n\n curr tokentype : %d\n", parser->current_token->type);
	// while (parser->current_token != NULL && parser->current_token->type != TOKEN_OP_PIPE)
	// {
	// 	printf("\n\nhello from while\n");
	// 	if (parser->current_token->type != TOKEN_WORD)
	// 	{
	// 		if (parser->current_token->type == TOKEN_OP_REDIRECTION_IN)
	// 		{
	// 			command->redirect_in = ft_strdup(parser->current_token->next->value);
	// 			//not sure about open flags
	// 			command->infile_fd = open(command->redirect_in, O_RDONLY);
	// 			parser->current_token = parser->current_token->next;
	// 		}
	// 		else if (parser->current_token->type == TOKEN_OP_REDIRECTION_OUT)
	// 		{
	// 			command->redirect_out = ft_strdup(parser->current_token->next->value);
	// 			//not sure about open flags
	// 			command->outfile_fd = open(command->redirect_out, O_CREAT | O_WRONLY);
	// 			parser->current_token = parser->current_token->next;
	// 		}
	// 		else if (parser->current_token->type == TOKEN_OP_REDIRECTION_APPEND)
	// 		{
	// 			command->redirect_out = ft_strdup(parser->current_token->next->value);
	// 			//not sure about open flags
	// 			command->outfile_fd = open(command->redirect_out, O_CREAT | O_APPEND);
	// 			parser->current_token = parser->current_token->next;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		printf("\n\n error from loop 1 : %s\n", command->command[i]);
	// 		command->command[i] = ft_strdup(parser->current_token->value);
	// 		printf("\n\n error from loop 2 : %s\n", command->command[i]);
	// 		i++;
	// 	}
	// 	parser->current_token = parser->current_token->next;
	// }
	// printf("error: %s\n", command->command[0]);
	// command->path = find_command_path(command->command[0]);
	// //is it nessary to free stuff if path=NULL ? in execution there is checking for path
	// return (command);
// 	while (parser->current_token != NULL && parser->current_token->type != TOKEN_OP_PIPE)
// 	{
// 		printf("Parsing token: %s\n", parser->current_token->value); // Debug statement
// 		if (is_command(parser->current_token->type))
// 		{
// 			if (is_first_arg)
// 			{
// 			command->command = ft_strdup(parser->current_token->value);
// 			printf("Command: %s\n", command->command); // Debug statement

// 			//find command path
// 			command->path = find_command_path(command->command);
// 			if (command->path == NULL)
// 		    {
// 		        //printf("Error: Command path not found for %s\n", command->command); // Debug statement
// 		        free(command->command);
// 		        free(command);
// 				ft_perror(path_error);
// 		        return NULL;
// 		    }
// 			printf("Command path: %s\n", command->path); // Debug statement

// 			is_first_arg = 0;
// 			}
// 			else
// 			{
// 				if (get_arg(command, parser->current_token->value) == 1)// what shall i pass to it?
// 		        {
// 		            //printf("Error: Failed to get argument %s\n", parser->current_token->value); // Debug statement
// 		            free(command->command);
// 		            free(command->path);
// 		            free(command);
// 		            return (NULL); // malloc error - lethal
// 		        }
// 			}
// 		}
// 		if (is_redirection(parser->current_token->type))// is token any of the redirect types?
// 			parse_redirection(command, parser);
// 		advance_token(parser);
// 	}
// 	return (command);
// }

t_parser	*parser_init(t_tokenlist *tokenlist)
{
	t_parser *parser;
	parser = malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	parser->tokenlist = tokenlist;
	parser->current_token = tokenlist->head;
	return (parser);
}

t_command	*parse(t_parser *parser, t_tokenlist *tokenlist)
{
	t_command *commandlist;
	t_command *last_command;
	t_command *current_command;

	commandlist = NULL;
	last_command = NULL;

	if (syntax_checker(tokenlist) == -1)
	{
		tokenlist_free(tokenlist);
		//return (ft_perror(syntax_error), NULL);
		return NULL;
	}
	while (parser->current_token != NULL)
	{
		//printf("Current token: %s\n", parser->current_token->value); // Debug statement

		current_command = parse_command(parser);
		if (current_command == NULL)
		{
			//printf("Error parsing command\n"); // lethal?
			return (NULL); // lethal
		}
		if (commandlist == NULL)
			commandlist = current_command;
		else
			last_command->next = current_command;
		last_command = current_command;
		if (parser->current_token && is_pipe(parser->current_token->type))
			advance_token(parser);
	}
	return (commandlist);
}
