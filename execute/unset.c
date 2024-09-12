#include "lexer.h"

void	ft_unset(t_lexer *lexer)
{
	int		i;
	t_env	*current;
	t_env	*previous;

	i = 1;
	while (lexer->tokens[i])
	{
		current = lexer->env;
		previous = NULL:
		while (current)
		{
			if (strcmp(current->key, lexer->tokens[i]) == 0)
			{
				if (previous == NULL)
				{
					lexer->env = current->next;
				}
				else
				{
					previous->next = current->next;
				}
				free (current);
				break;
			}
			previous = current;
			current = curent->next;
		}
	}
}