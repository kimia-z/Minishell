/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 14:07:08 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/20 12:01:44 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_word_token(char c)
{
	return (c != '\0' && (ft_isalnum(c) || c == '_' || c == '-' || \
	c == '.' || c == '/' || c == '^' || c == '_'));
}

bool	is_operator_token(char c)
{
	return (c != '\0' && !ft_isalnum(c) && c != ' ' && c != '\t' && c != '\n');
}

bool	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}
