/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim_quotes_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/23 13:36:51 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 13:42:57 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"

void	process_quotes(char **value, char *quote_start, char *quote_end)
{
	char	*new_value;
	size_t	len_before;
	size_t	len_after;

	len_before = quote_start - *value;
	len_after = ft_strlen(quote_end + 1);
	new_value = malloc(len_before + (quote_end - quote_start - 1) + \
	len_after + 1);
	if (new_value)
	{
		ft_strncpy(new_value, *value, len_before);
		ft_strncpy(new_value + len_before, quote_start + 1, quote_end - \
		quote_start - 1);
		ft_strcpy(new_value + len_before + (quote_end - quote_start - 1), \
		quote_end + 1);
		free(*value);
		*value = new_value;
	}
}

void	trim_quotes_from_tokenlist(t_tokenlist *tokenlist)
{
	t_token	*current_token;

	current_token = tokenlist->head;
	while (current_token)
	{
		trim_quotes_from_token(&current_token->value);
		current_token = current_token->next;
	}
}

void	trim_quotes_from_token(char **value)
{
	char	*quote_start;
	char	*quote_end;

	quote_start = ft_strchr(*value, '\'');
	if (!quote_start)
		quote_start = ft_strchr(*value, '"');
	while (quote_start)
	{
		quote_end = ft_strrchr(*value, *quote_start);
		if (quote_end && quote_end != quote_start)
			process_quotes(value, quote_start, quote_end);
		else
			break ;
		quote_start = ft_strchr(*value, '\'');
		if (!quote_start)
			quote_start = ft_strchr(*value, '"');
	}
}
