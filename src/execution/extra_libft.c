/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   extra_libft.c                                      :+:      :+:    :+:   */
/*                                                      +:+                   */
/*   By: kziari <marvin@42.fr>                         +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/11 13:18:17 by kziari         #+#    #+#                */
/*   Updated: 2024/12/12 13:49:29 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_strchr_pos(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	return (0);
}

int	my_lstsize(t_env *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_env	*my_lstnew(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(1 * sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env	*my_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	my_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = my_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
