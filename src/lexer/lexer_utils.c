/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 21:06:47 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 14:23:08 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lexer_init(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	ft_bzero(lexer, sizeof(t_lexer));
	//printf("from lexer_init, input is: %s\n", input);
	lexer->input = ft_strdup(input);
	if (!lexer->input)
		return (free(lexer), NULL);
	//printf("from lexer_init after ft_strdup, input is: %s\n", lexer->input);
	lexer->tokens = NULL;
	lexer->position = 0;
	lexer->length = ft_strlen(input);
	lexer->start = 0;
	return (lexer);
}

void	lexer_free(t_lexer *lexer)
{
	if (!lexer)
		return ;
	free(lexer->input);
	free(lexer);
}

/* updates the struct */
void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->position < lexer->length && ft_isspace(lexer->input[lexer->position]))
		lexer->position++;
}

bool	is_quote_closed(t_lexer *lexer, char quote_char)
{
	return (ft_strchr(lexer->input + lexer->position + 1, quote_char) != NULL);
}
