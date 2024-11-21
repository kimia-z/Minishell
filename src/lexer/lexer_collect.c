/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_collect.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:00:24 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/19 22:26:41 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

enum e_token_type	get_operator_type(char *value)
{
	if (*value == '>' && *(value + 1) == '>')
		return (TOKEN_OP_REDIRECTION_APPEND);
	else if (*value == '<')
		return (TOKEN_OP_REDIRECTION_IN);
	else if (*value == '>')
		return (TOKEN_OP_REDIRECTION_OUT);
	else if (*value == '|')
		return (TOKEN_OP_PIPE);
	else
		return (TOKEN_UNKNOWN);
}


void	*lexer_collect_token(t_lexer *lexer, t_tokenlist *tokenlist, bool is_op, int pos)
{
	size_t	start;
	size_t	len;
	char	*word;
	t_token	*token;
	int		op_type;

	lexer_skip_whitespace(lexer);
	start = lexer->position;
	while (lexer->position < lexer->length && !ft_isspace(lexer->input[lexer->position]))
		lexer->position++;
	len = lexer->position - start;
	word = ft_strndup(lexer->input + start, len);
	if (!word)
		return (NULL);
	if (is_op == true)
	{
		op_type = get_operator_type(word);
		token = token_create(op_type, word);
		if (!token)
			return (free(word), NULL);
	}
	else
	{
		token = token_create(TOKEN_WORD, word);
		if (!token)
			return (free(word), NULL);
	}
	tokenlist_add(tokenlist, token);
	free(word);
	return (token);
}

