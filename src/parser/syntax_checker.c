/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_checker.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 17:21:55 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 13:16:22 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

static bool	is_invalid_position(size_t position, size_t token_count)
{
	return (position == 0 || position == token_count - 1);
}

static int	is_operator(enum e_token_type type)
{
	return (type == TOKEN_OP_PIPE);
}

static int	operator_checker(enum e_token_type type, size_t position, size_t \
token_count, enum e_token_type left_op)
{
	if (is_operator(type) && (is_invalid_position(position, token_count) \
	|| is_operator(left_op)))
		return (1);
	return (0);
}

int	syntax_checker(t_tokenlist *tokenlist)
{
	t_token				*temp;
	size_t				i;
	enum e_token_type	left_op;

	i = 0;
	left_op = TOKEN_WORD;
	temp = tokenlist->head;
	while (temp != NULL)
	{
		if (is_operator(temp->type))
		{
			if (operator_checker(temp->type, i, \
			tokenlist->token_count, left_op) == 1)
				return (perror("syntax"), -1);
		}
		i++;
		left_op = temp->type;
		temp = temp->next;
	}
	return (0);
}
