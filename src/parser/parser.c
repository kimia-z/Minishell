/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 17:49:42 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/26 17:59:35 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"


/*
is there a difference whether in/append/out comes first?
*/
void parse_redirection(t_command *command, t_token **current_token)
{
	if ((*current_token)->type == TOKEN_OP_REDIRECTION_APPEND)
	{
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


static int	handle_first_arg(t_command *command, t_token *current_token)
{
	//printf("Handling first argument: %s\n", current_token->value);
	command->command = malloc(2 * sizeof(char *));
	if (!command->command)
		return (-1);
	command->command[0] = ft_strdup(current_token->value);
	if (!command->command[0])
		return (free(command->command), -1);
	//printf("First argument: %s\n", command->command[0]);
	command->command[1] = NULL;
	command->path = find_command_path(command->command[0]);
	if (!command->path)
	{
		free(command->command[0]);
		free(command->command);
		return (-1);
	}
	//printf("Command path: %s\n", command->path);
	return (0);
}

static int	handle_subsequent_args(t_command *command, t_token *current_token, int command_count)
{
	//printf("Handling subsequent argument: %s\n", current_token->value);
	char	**new_command;

	new_command = realloc(command->command, (command_count + 2) * sizeof(char *));
	if (!new_command)
		return (-1);
	command->command = new_command;
	//printf("from sub arg, cmd count: %d\n", command_count);
	command->command[command_count] = ft_strdup(current_token->value);
	if (!command->command[command_count])
		return (-1);
	//printf("Subsequent argument[%d]: %s\n", command_count, command->command[command_count]);
	command->command[command_count + 1] = NULL;
	return (0);
}


t_command	*parse_command(t_token **current_token)
{
	t_command	*command;
	int			command_count;

	command_count = 0;
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	ft_bzero(command, sizeof(t_command));
	while (*current_token && (*current_token)->type != TOKEN_OP_PIPE)
	{
		if (is_command((*current_token)->type))
		{
			if (command_count == 0)
			{
				if (handle_first_arg(command, *current_token) == -1)
					return (free(command), NULL);
			}
			else
			{
				if (handle_subsequent_args(command, *current_token, command_count) == -1)
					return (free_command_resources(command, command_count), NULL);
			}
			command_count++;
		}
		if (is_redirection((*current_token)->type))
			parse_redirection(command, current_token);
		*current_token = (*current_token)->next;
	}
	return (command);
}


/*
NULL on failure: cmdinit malloc fails - 
*/
t_cmdlist	*parser(t_tokenlist *tokenlist)
{
	t_command	*last_command;
	t_command	*current_command;
	t_cmdlist	*cmdlist;
	t_token		*current_token;

	last_command = NULL;
	current_token = tokenlist->head;
	cmdlist = cmdlist_init();
	if (!cmdlist)
		return (NULL);
	while (current_token != NULL)
	{
		current_command = parse_command(&current_token);
		if (!current_command)
		{
			free_command_list(cmdlist);
			return (NULL);
		}
		if (!cmdlist->head) // first command
			cmdlist->head = current_command;
		else
			last_command->next = current_command;
		cmdlist->num_commands++;
		last_command = current_command;
		if (current_token && is_pipe(current_token->type))
			current_token = current_token->next;
	}
	return (cmdlist);
}

