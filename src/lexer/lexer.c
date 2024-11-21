/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 21:15:24 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/19 22:36:07 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//TODO
// add when char c = $... so it should call expander the create token
// add here_doc

static bool is_word_token(char c)
{
	return (c != '\0' && (ft_isalpha(c) || c == '_' || c == '-'));
}

static bool	is_operator_token(char c)
{
	return (c != '\0' && !ft_isalnum(c));
}

static bool	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

int	lexer_main(t_lexer *lexer, t_tokenlist *tokenlist)
{
	char	current_char;
	bool	is_op;
	int		pos;

	pos = 1;
	while (lexer->position < lexer->length)
	{
		lexer_skip_whitespace(lexer);
		current_char = lexer->input[lexer->position];
		is_op = false;
		if (is_word_token(current_char) == true)
		{
			if (!lexer_collect_token(lexer, tokenlist, is_op, pos))
				return (-1);
			pos++;
		}
		else if (is_operator_token(current_char))
		{
			is_op = true;
			if (!lexer_collect_token(lexer, tokenlist, is_op, pos))
				return (-1);
			pos++;
		}
		else if (is_quotes(current_char))
		{
			is_op = false;
			if (!lexer_collect_quotes(lexer, &current_char, tokenlist, is_op, pos))
				return (-1);
			pos++;
		}
		lexer->position++;
	}
	return (0);
}
