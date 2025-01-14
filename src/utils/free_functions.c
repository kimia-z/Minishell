/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 17:57:00 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/10 17:57:46 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void	free_nullify(void **thing)
{
	if (*thing != NULL)
	{
		free(*thing);
		*thing = NULL;
	}
}

void	free_2d(void ***thing)
{
	int		i;
	void	**arr;

	i = 0;
	if (*thing == NULL)
		return ;
	arr = *thing;
	while (arr[i] != NULL)
	{
		free_nullify(&arr[i]);
		i++;
	}
	free(arr);
	*thing = NULL;
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	if (command->command != NULL)
	{
		while (command->command[i])
		{
			free(command->command[i]);
			i++;
		}
		free(command->command);
	}
	if (command->redirect_in != NULL)
		free(command->redirect_in);
	if (command->redirect_out != NULL)
		free(command->redirect_out);
	if (command->path != NULL)
		free(command->path);
	free(command);
}

void	free_command_list(t_cmdlist *cmdlist)
{
	t_command	*current;
	t_command	*next;

	if (!cmdlist)
		return ;
	current = cmdlist->head;
	while (current != NULL)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
	free(cmdlist);
}
