/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   space_putter.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kziari <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/20 11:28:34 by kziari        #+#    #+#                 */
/*   Updated: 2024/12/23 14:31:11 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"

static int	quotes(char *input, int pos)
{
	int	i;
	int	base;
	int	count;

	count = 0;
	i = 0;
	base = 0;
	while (input[i] && i <= pos)
	{
		if (input[i] == '\'' && (base == 0 || base == 1))
		{
			count++;
			base = 1;
		}
		if (input[i] == '"' && (base == 0 || base == 2))
		{
			count++;
			base = 2;
		}
		i++;
		if (count % 2 == 0)
			base = 0;
	}
	return (base);
}

static void	the_inserter(char *input, char *new_input, int *i, int *j)
{
	if ((input[*i] == '<' || input[*i] == '>') && !quotes(input, *i) && \
		(*i == 0 || new_input[*j - 1] != input[*i]))
	{
		if (*i == 0 || input[*i - 1] != ' ')
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		if (input[*i] && input[*i] == input[*i - 1])
			new_input[(*j)++] = input[(*i)++];
		if (input[*i] && input[*i] != ' ' && !quotes(input, (*i) - 1))
			new_input[(*j)++] = ' ';
	}
	else if (input[*i] == '|' && !quotes(input, *i))
	{
		if (*i == 0 || input[*i - 1] != ' ')
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		if (input[*i] && input[*i] != ' ' && !quotes(input, *i))
			new_input[(*j)++] = ' ';
	}
	else
		new_input[(*j)++] = input[(*i)++];
	return ;
}

char	*space_putter(char *input)
{
	char	*new_input;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_input = (char *)malloc((3 * strlen(input) + 1) * sizeof(char));
	if (!new_input)
		return (NULL);
	while (input[i])
		the_inserter(input, new_input, &i, &j);
	new_input[j] = 0;
	return (new_input);
}
