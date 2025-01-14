/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_collect.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:00:24 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/22 09:17:52 by yasamankari   ########   odam.nl         */
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

char	*collect_word(t_lexer *lexer)
{
	size_t	start;
	size_t	len;
	char	*word;

	lexer_skip_whitespace(lexer);
	start = lexer->position;
	while (lexer->position < lexer->length && \
	!ft_isspace(lexer->input[lexer->position]))
		lexer->position++;
	len = lexer->position - start;
	word = ft_strndup(lexer->input + start, len);
	return (word);
}

static char	*expand_word(char *word, char **envp)
{
	char	*expanded_word;
	char	*sign;

	sign = ft_strchr(word, '$');
	if (sign && ft_strncmp(sign + 1, "?", 1) != 0)
	{
		expanded_word = expand_variables(word, envp);
		free(word);
		word = expanded_word;
	}
	return (word);
}

static t_token	*create_token(char *word, bool is_op)
{
	t_token	*token;
	int		op_type;

	if (is_op)
	{
		op_type = get_operator_type(word);
		token = token_create(op_type, word);
	}
	else
		token = token_create(TOKEN_WORD, word);
	return (token);
}

void	*lexer_collect_token(t_lexer *lexer, t_tokenlist *tokenlist, \
bool is_op, char **envp)
{
	char	*word;
	t_token	*token;

	word = collect_word(lexer);
	if (!word)
		return (NULL);
	word = expand_word(word, envp);
	if (!word)
		return (NULL);
	token = create_token(word, is_op);
	if (!token)
		return (free(word), NULL);
	tokenlist_add(tokenlist, token);
	free(word);
	return (token);
}
