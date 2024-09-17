#include "parser.h"
#include "lexer.h"

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
			command->redirect_append = ft_strdup(parser->current_token->value);
	}
	else if (parser->current_token->type == TOKEN_OP_REDIRECTION_OUT)
	{
		advance_token(parser);
		if (parser->current_token && is_command(parser->current_token->type))
			command->redirect_out = ft_strdup(parser->current_token->value);
	}
	else if (parser->current_token->type == TOKEN_OP_REDIRECTION_IN)
	{
		advance_token(parser);
		if (parser->current_token && is_command(parser->current_token->type))
			command->redirect_in = ft_strdup(parser->current_token->value);
	}
}

// check>??
int get_arg(t_command *command, char *value)
{
	char	**new_args;
    int i = 0;
	int j = 0;

    // Count the existing arguments
    if (command->args != NULL)
    {
        while (command->args[i] != NULL)
            i++;
    }

    // Allocate memory for the new argument array
    new_args = malloc((i + 2) * sizeof(char *));
    if (new_args == NULL)
    {
        perror("malloc");
        return (1);
    }

    // Copy existing arguments to the new array
	while (j < i)
    {
        new_args[j] = command->args[j];
		j++;
    }

    // Add the new argument
    new_args[i] = ft_strdup(value);
    new_args[i + 1] = NULL;

    // Free the old args array if it exists
    if (command->args != NULL)
        free(command->args);

    // Update the command's args array
    command->args = new_args;
	return (0);
}


t_command	*parse_command(t_parser *parser)
{
	t_command *command;
	int is_first_arg = 1;
	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->command = NULL;
	command->args = NULL;
	command->path = NULL;
	command->redirect_in = NULL;
	command->redirect_out = NULL;
	command->redirect_append = NULL;
	command->next = NULL;
	while (parser->current_token != NULL && parser->current_token->type != TOKEN_OP_PIPE)
	{
		if (is_command(parser->current_token->type))
		{
			if (is_first_arg)
			{
			command->command = ft_strdup(parser->current_token->value);
			//find command path
			command->path = find_command_path(command->command);
			if (command->path == NULL)
				return (NULL);
			is_first_arg = 0;
			}
			else
			{
				if (get_arg(command, parser->current_token->value) == 1)// what shall i pass to it?
					return (NULL);
			}
		}
		if (is_redirection(parser->current_token->type))// is token any of the redirect types?
			parse_redirection(command, parser);
		advance_token(parser);
	}
	return (command);

}

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

	if (syntax_checker(tokenlist) == 1)
	{
		printf("error\n");
		tokenlist_free(tokenlist);
		exit(EXIT_FAILURE);
	}
	while (parser->current_token != NULL)
	{
		current_command = parse_command(parser);
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
