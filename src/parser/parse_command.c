/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 16:30:00 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 14:19:12 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"

int	handle_redirections(t_command *command, \
t_token **current_token)
{
	if (is_redirection((*current_token)->type))
	{
		if (parse_redirection(command, current_token) == -1)
			return (-1);
	}
	return (0);
}

void	initialize_command(t_command *command)
{
	int	i;

	i = 0;
	ft_bzero(command, sizeof(t_command));
	command->infile_fd = -2;
	command->outfile_fd = -2;
	command->is_quotes = malloc(sizeof(bool) * MAX_CMD_ARGS);
	while (i < MAX_CMD_ARGS)
		command->is_quotes[i++] = false;
}

int	process_command_args(t_command *command, t_token **current_token, \
						int *command_count, t_data *data)
{
	if (handle_command_args(command, current_token, command_count) == -1)
	{
		data->exit_status = ERROR_GENERIC;
		return (-1);
	}
	command->is_quotes[*command_count - 1] = (*current_token)->is_single_quotes;
	return (0);
}

int	process_tokens(t_command *command, t_token **current_token, \
					int *command_count, t_data *data)
{
	while (*current_token && (*current_token)->type != TOKEN_OP_PIPE)
	{
		if (is_command((*current_token)->type) || (*current_token)->type \
			== TOKEN_UNKNOWN)
		{
			if (process_command_args(command, current_token,
					command_count, data) == -1)
				return (-1);
		}
		if (handle_redirections(command, current_token) == -1)
			return (-1);
		*current_token = (*current_token)->next;
	}
	return (0);
}

t_command	*parse_command(t_token **current_token, t_data *data)
{
	t_command	*command;
	int			command_count;

	command_count = 0;
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	initialize_command(command);
	if (process_tokens(command, current_token, &command_count, data) == -1)
		return (free_command_resources(command, command_count), (NULL));
	return (command);
}
