/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 16:42:09 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/19 16:04:19 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_pipe(enum e_token_type type)
{
	if (type == TOKEN_OP_PIPE)
		return (true);
	return (false);
}

bool	is_redirection(enum e_token_type type)
{
	if (type == TOKEN_OP_REDIRECTION_APPEND || type == TOKEN_OP_REDIRECTION_IN \
	|| type == TOKEN_OP_REDIRECTION_OUT || type == TOKEN_OP_HEREDOC)
		return (true);
	return (false);
}

bool	is_command(enum e_token_type type)
{
	if (type == TOKEN_WORD)
		return (true);
	return (false);
}

t_cmdlist	*cmdlist_init(void)
{
	t_cmdlist	*cmdlist;

	cmdlist = malloc(sizeof(t_cmdlist));
	if (!cmdlist)
		return (NULL);
	ft_bzero(cmdlist, sizeof(t_cmdlist));
	return (cmdlist);
}

void	free_command_resources(t_command *command, int command_count)
{
	int	i;

	i = 0;
	while (i < command_count)
	{
		free(command->command[i]);
		i++;
	}
	free(command->command);
	if (command->path != NULL)
		free(command->path);
	free(command);
}
