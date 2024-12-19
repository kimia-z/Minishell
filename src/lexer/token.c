/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 21:25:13 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 14:47:53 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Create a new token of the given type and value */
t_token	*token_create(enum e_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
		return (free(token), NULL);
	token->next = NULL;
	return (token);
}

void	token_free(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}
