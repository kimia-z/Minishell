/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:46:31 by kziari            #+#    #+#             */
/*   Updated: 2024/12/09 10:46:34 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	if pipe exist unset ignored
	if without argument ignored
	examples:
	*- unset USER PWD
*/

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

static void	ft_unset_helper(t_env *previous, t_env *current, t_data *data)
{
	if (previous == NULL)
		data->env = current->next;
	else
		previous->next = current->next;
	free (current->key);
	free (current->value);
	free (current);
}

static void	set_status(t_data *data)
{
	data->exit_status = SUCCESS;
}

void	ft_unset(t_command *commands, t_data *data, int nb_pipes)
{
	int		i;
	t_env	*current;
	t_env	*previous;

	i = 0;
	if (nb_pipes > 0 || !commands->command[1])
		return (set_status(data));
	while (commands->command[++i])
	{
		current = data->env;
		previous = NULL;
		while (current != NULL)
		{
			if (ft_strcmp(current->key, commands->command[i]) == 0)
			{
				ft_unset_helper(previous, current, data);
				break ;
			}
			previous = current;
			current = current->next;
		}
	}
	data->exit_status = SUCCESS;
}
