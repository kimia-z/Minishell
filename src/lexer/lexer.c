/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 21:15:24 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 14:42:10 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	handle_quotes(t_lexer *lexer, t_tokenlist *tokenlist, char **envp)
{
	char	current_char;
	bool	is_op;

	current_char = lexer->input[lexer->position];
	is_op = false;
	if (lexer_collect_quotes(lexer, &current_char, tokenlist, is_op, envp) \
	== -1)
		return (-1);
	return (0);
}

static int	handle_dollar_or_word(t_lexer *lexer, t_tokenlist *tokenlist, \
char **envp)
{
	bool	is_op;

	is_op = false;
	if (!lexer_collect_token(lexer, tokenlist, is_op, envp))
		return (-1);
	return (0);
}

static int	handle_operator(t_lexer *lexer, t_tokenlist *tokenlist, char **envp)
{
	bool	is_op;

	is_op = true;
	if (!lexer_collect_token(lexer, tokenlist, is_op, envp))
		return (-1);
	return (0);
}

int	lexer_main(t_lexer *lexer, t_tokenlist *tokenlist, char **envp)
{
	char	current_char;

	while (lexer->position < lexer->length)
	{
		lexer_skip_whitespace(lexer);
		current_char = lexer->input[lexer->position];
		if (is_quotes(current_char))
		{
			if (handle_quotes(lexer, tokenlist, envp) == -1)
				return (-1);
		}
		else if (current_char == '$' || is_word_token(current_char))
		{
			if (handle_dollar_or_word(lexer, tokenlist, envp) == -1)
				return (-1);
		}
		else if (is_operator_token(current_char))
		{
			if (handle_operator(lexer, tokenlist, envp) == -1)
				return (-1);
		}
		lexer->position++;
	}
	return (0);
}
