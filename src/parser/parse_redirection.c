/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirection.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 16:05:38 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 13:14:51 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"

static int	handle_redirection_append(t_command *command, \
t_token **current_token)
{
	*current_token = (*current_token)->next;
	if (*current_token && is_command((*current_token)->type))
	{
		command->redirect_out = ft_strdup((*current_token)->value);
		command->outfile_fd = open(command->redirect_out, O_WRONLY | \
		O_CREAT | O_APPEND, 0644);
		if (command->outfile_fd == -1)
			perror("open failed");
	}
	return (0);
}

static int	handle_redirection_out(t_command *command, t_token **current_token)
{
	*current_token = (*current_token)->next;
	if (*current_token && is_command((*current_token)->type))
	{
		command->redirect_out = ft_strdup((*current_token)->value);
		command->outfile_fd = open(command->redirect_out, O_WRONLY | O_CREAT \
		| O_TRUNC, 0644);
		if (command->outfile_fd == -1)
			perror("open failed");
	}
	return (0);
}

static int	handle_redirection_in(t_command *command, t_token **current_token)
{
	*current_token = (*current_token)->next;
	if (*current_token && is_command((*current_token)->type))
	{
		command->redirect_in = ft_strdup((*current_token)->value);
		command->infile_fd = open(command->redirect_in, O_RDONLY);
		if (command->infile_fd == -1)
			perror("open failed");
	}
	return (0);
}

static int	handle_redirection_heredoc(t_command *command, \
t_token **current_token)
{
	int	heredoc_fd;

	*current_token = (*current_token)->next;
	if (*current_token && is_command((*current_token)->type))
	{
		heredoc_fd = handle_heredoc((*current_token)->value);
		command->infile_fd = open(command->redirect_in, O_CREAT | \
		O_RDWR | O_TRUNC);
		if (heredoc_fd == -1)
			return (-1);
		command->infile_fd = heredoc_fd;
	}
	return (0);
}

int	parse_redirection(t_command *command, t_token **current_token)
{
	if ((*current_token)->type == TOKEN_OP_REDIRECTION_APPEND)
		return (handle_redirection_append(command, current_token));
	else if ((*current_token)->type == TOKEN_OP_REDIRECTION_OUT)
		return (handle_redirection_out(command, current_token));
	else if ((*current_token)->type == TOKEN_OP_REDIRECTION_IN)
		return (handle_redirection_in(command, current_token));
	else if ((*current_token)->type == TOKEN_OP_HEREDOC)
		return (handle_redirection_heredoc(command, current_token));
	return (0);
}
