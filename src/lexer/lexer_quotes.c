/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/05 22:03:33 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/23 13:10:45 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

/* Calculates the length of the quoted section */
static size_t	len_quotes(const char *value, char quote_char)
{
	size_t	i;

	i = 1;
	while (value[i] && value[i] != quote_char)
		i++;
	return (i - 1);
}

char	*extract_quoted_string(t_lexer *lexer, char quote_char)
{
	size_t	len;
	char	*token_value;

	if (!is_quote_closed(lexer, quote_char))
		return (NULL);
	len = len_quotes(lexer->input + lexer->position, quote_char);
	lexer->position++;
	token_value = ft_substr(lexer->input, lexer->position, len);
	lexer->position += len + 1;
	return (token_value);
}

char	*expand_if_double_quotes(char *token_value, char quote_char, \
char **envp)
{
	char	*expanded_value;

	if (quote_char == '"')
	{
		expanded_value = expand_variables(token_value, envp);
		if (expanded_value == NULL)
		{
			return (token_value);
		}
		else
		{
			free(token_value);
			return (expanded_value);
		}
	}
	return (token_value);
}

int	create_and_add_token(t_tokenlist *tokenlist, char *token_value, \
						char quote_char)
{
	t_token	*token;

	token = token_create(TOKEN_WORD, token_value);
	if (!token)
	{
		free(token_value);
		return (-1);
	}
	token->is_single_quotes = (quote_char == '\'');
	tokenlist_add(tokenlist, token);
	free(token_value);
	return (0);
}

int	lexer_collect_quotes(t_lexer *lexer, t_tokenlist *tokenlist, char **envp)
{
	char	*token_value;
	char	quote_char;

	quote_char = lexer->input[lexer->position];
	token_value = extract_quoted_string(lexer, quote_char);
	if (!token_value)
		return (-1);
	token_value = expand_if_double_quotes(token_value, quote_char, envp);
	if (create_and_add_token(tokenlist, token_value, quote_char) == -1)
		return (-1);
	if (lexer->input[lexer->position] == '\'' || \
	lexer->input[lexer->position] == '"')
		return (-1);
	return (0);
}
