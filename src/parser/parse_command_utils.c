/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_command_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/23 13:59:28 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 14:20:32 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"

int	handle_first_arg(t_command *command, t_token *current_token)
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

int	handle_subsequent_args(t_command *command, \
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

int	handle_command_args(t_command *command, \
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
