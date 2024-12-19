/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 16:30:00 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/19 16:38:39 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"

static int	handle_first_arg(t_command *command, t_token *current_token)
{
	command->command = malloc(2 * sizeof(char *));
	if (!command->command)
		return (-1);
	command->command[0] = ft_strdup(current_token->value);
	if (!command->command[0])
		return (free(command->command), -1);
	command->command[1] = NULL;
	return (0);
}

static int	handle_subsequent_args(t_command *command, \
t_token *current_token, int command_count)
{
	char	**new_command;

	new_command = ft_realloc(command->command, \
	(command_count + 1) * sizeof(char *), (command_count + 2) * sizeof(char *));
	if (!new_command)
		return (-1);
	command->command = new_command;
	command->command[command_count] = ft_strdup(current_token->value);
	if (!command->command[command_count])
		return (-1);
	command->command[command_count + 1] = NULL;
	return (0);
}

static int	handle_command_args(t_command *command, \
t_token **current_token, int *command_count)
{
	if (*command_count == 0)
	{
		if (handle_first_arg(command, *current_token) == -1)
			return (-1);
	}
	else
	{
		if (handle_subsequent_args(command, *current_token, \
		*command_count) == -1)
			return (-1);
	}
	(*command_count)++;
	return (0);
}

static int	handle_redirections(t_command *command, \
t_token **current_token)
{
	if (is_redirection((*current_token)->type))
	{
		if (parse_redirection(command, current_token) == -1)
			return (-1);
	}
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
	command->infile_fd = -2;
	command->outfile_fd = -2;
	while (*current_token && (*current_token)->type != TOKEN_OP_PIPE)
	{
		if (is_command((*current_token)->type))
		{
			if (handle_command_args(command, current_token, \
			&command_count) == -1)
				return (free_command_resources(command, command_count), NULL);
		}
		if (handle_redirections(command, current_token) == -1)
			return (free_command_resources(command, command_count), NULL);
		*current_token = (*current_token)->next;
	}
	return (command);
}
