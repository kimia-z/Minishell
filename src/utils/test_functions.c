/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 19:17:01 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/10 18:00:52 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"


void print_command(t_command *command)
{
	int i = 0;

	if (!command)
		return;
	if (command->command)
	{
		//printf("Arguments:\n");
		while (command->command[i])
		{
			printf(" command[%d]: %s.\n", i, command->command[i]);
			i++;
		}
	}
	if (command->redirect_in)
		printf("Redirect in: %s\n", command->redirect_in);
	if (command->redirect_out)
		printf("Redirect out: %s\n", command->redirect_out);
	if (command->redirect_append)
		printf("Redirect append: %s\n", command->redirect_append);
}


void print_command_list(t_cmdlist *commandlist)
{
	t_command *current;

	if (!commandlist)
		return;

	printf("Number of commands: %zu\n", commandlist->num_commands);
	current = commandlist->head;
	while (current)
	{
		print_command(current);
		current = current->next;
	}
}


void tokenlist_print(t_token *head)
{
	int i = 0;
	t_token *current = head;
	while (current != NULL)
	{
		printf("%d  - ", i);
		printf("Token Type: %d, Token Value: %s", current->type, current->value);
		current = current->next;
		i++;
	}
}

void print_envp(char **envp)
{
	int i = 0;
	if (!envp)
	{
		printf("envp is NULL\n");
		return;
	}
	printf("envp contents:\n");
	while (envp[i])
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		i++;
	}
}

void print_env_list(t_env *env_list)
{
	t_env *current = env_list;
	if (!env_list)
	{
		printf("env_list is NULL\n");
		return;
	}
	printf("env_list contents:\n");
	while (current)
	{
		printf("key: %s, value: %s\n", current->key, current->value);
		current = current->next;
	}
}