/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 12:41:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/19 22:38:18 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//TODO
// for exit_shell, include a scenario when it's not error and you wanna exit
// make functions that display error in different situations
// malloced resources: prompt - commands - history - env var - 


/* Writing errors to STDERR */
void	write_stderr(char *errmsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	free_command(t_command *command)
{
	if (command == NULL)
		return;
	if (command->command != NULL)
		free(command->command);
	if (command->redirect_in != NULL)
		free(command->redirect_in);
	if (command->redirect_out != NULL)
		free(command->redirect_out);
	if (command->redirect_append != NULL)
		free(command->redirect_append);
	free(command);
}

void	free_command_list(t_command *cmdlist)
{
	t_command	*current;
	t_command	*next;

	current = cmdlist;
	while (current != NULL)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
}


void	cleanup_memory_alloc(t_data *data)
{
	free_2d(data->envp);
	free_env_list(data->env);
	free_history(&data->history); // is it doing its job?
	
}

/* when things went well and you wanna exit */
void	end_shell(t_data *data)
{
	//free all malloced
	//reset_terminal();
	//close_fds();
	cleanup_memory_alloc(data);
}


void	free_nullify(void **thing)
{
	free(*thing);
	*thing = NULL;
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

