/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_collect.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:00:24 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/05 22:03:02 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

enum e_token_type	get_operator_type(char *value)
{
	if (*value == '>' && *(value + 1) == '>')
		return (TOKEN_OP_REDIRECTION_APPEND);
	else if (*value == '<' && *(value + 1) == '<')
		return (TOKEN_OP_HEREDOC);
	else if (*value == '<')
		return (TOKEN_OP_REDIRECTION_IN);
	else if (*value == '>')
		return (TOKEN_OP_REDIRECTION_OUT);
	else if (*value == '|')
		return (TOKEN_OP_PIPE);
	else if (*value == '\'')
		return (TOKEN_SINGLE_QUOTES);
	else if (*value == '"')
		return (TOKEN_DOUBLE_QUOTES);
	else if (*value == '$')
		return (TOKEN_DOLLA);
	else
		return (TOKEN_UNKNOWN);
}

void	*lexer_collect_token(t_lexer *lexer, t_tokenlist *tokenlist, bool is_op, char **envp)
{
	size_t	start;
	size_t	len;
	char	*word;
	t_token	*token;
	int		op_type;
	char	*expanded_word;

	lexer_skip_whitespace(lexer);
	start = lexer->position;
	while (lexer->position < lexer->length && !ft_isspace(lexer->input[lexer->position]))
		lexer->position++;
	len = lexer->position - start;
	word = ft_strndup(lexer->input + start, len);
	if (!word)
		return (NULL);
    if (ft_strchr(word, '$'))
    {
        expanded_word = expand_variables(word, envp);
        free(word);
        word = expanded_word;
    }
	if (is_op == true)
	{
		op_type = get_operator_type(word);
		token = token_create(op_type, word);
		if (!token)
			return (free(word), NULL);
		//printf("Collected operator token: %s, type: %d\n", word, op_type);
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

