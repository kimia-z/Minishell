#include "execution.h"

/*
	if pipe exist unset ignored
	if without argument ignored
	examples:
	*- unset USER PWD
*/

void	ft_unset(t_command *commands, t_data *data, int nb_pipes)
{
	int		i;
	t_env	*current;
	t_env	*previous;

	i = 1;
	if (nb_pipes > 0 || !commands->command[1])
	{
		data->exit_status = 0;
		//test_print_env(parser->envs);
		return ;
	}
	while (commands->command[i])
	{
		current = data->env;
		previous = NULL;
		while (current != NULL)
		{
			if (strcmp(current->key, commands->command[i]) == 0)
			{
				if (previous == NULL)
				{
					data->env = current->next;
				}
				else
				{
					previous->next = current->next;
				}
				free(current->key);
				free(current->value);
				free (current);
				break;
			}
			previous = current;
			current = current->next;
		}
		i++;
	}
	data->exit_status = 0;
	//test_print_env(parser->envs);
}