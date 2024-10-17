/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 16:42:09 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/09/12 16:42:11 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool is_pipe(enum e_token_type type)
{
	if (type == TOKEN_OP_PIPE)
		return (true);
	return (false);
}
bool is_redirection(enum e_token_type type)
{
	if (type == TOKEN_OP_REDIRECTION_APPEND || type == TOKEN_OP_REDIRECTION_IN || type == TOKEN_OP_REDIRECTION_OUT)
		return (true);
	return (false);
}

bool is_command(enum e_token_type type)
{
	if (type == TOKEN_WORD)
		return (true);
	return (false);
}
