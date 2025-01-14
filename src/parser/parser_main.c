/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 17:49:42 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/23 13:15:55 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"

static void	add_command_to_list(t_cmdlist *cmdlist, \
t_command *current_command, t_command **last_command)
{
	if (!cmdlist->head)
		cmdlist->head = current_command;
	else
		(*last_command)->next = current_command;
	cmdlist->num_commands++;
	*last_command = current_command;
}

int	parse_command_list(t_cmdlist *cmdlist, t_token **current_token, \
						t_data *data)
{
	t_command	*last_command;
	t_command	*current_command;

	last_command = NULL;
	while (*current_token != NULL)
	{
		current_command = parse_command(current_token, data);
		if (!current_command)
		{
			free_command_list(cmdlist);
			return (-1);
		}
		add_command_to_list(cmdlist, current_command, &last_command);
		if (*current_token && is_pipe((*current_token)->type))
			*current_token = (*current_token)->next;
	}
	return (0);
}

t_cmdlist	*parser_main(t_tokenlist *tokenlist, t_data *data)
{
	t_cmdlist	*cmdlist;
	t_token		*current_token;

	current_token = tokenlist->head;
	cmdlist = cmdlist_init();
	if (!cmdlist)
		return (NULL);
	if (parse_command_list(cmdlist, &current_token, data) == -1)
		return (NULL);
	return (cmdlist);
}
