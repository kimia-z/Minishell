/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:33:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 13:06:15 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"

static int	no_input(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v' && str[i] != '\n')
			return (0);
		i++;
	}
	return (-1);
}

static char	*retrieve_input(t_data *data)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt();
	if (!prompt)
	{
		data->exit_status = ERROR_GENERIC;
		write_stderr("failed to get prompt");
		return (NULL);
	}
	input = readline(prompt);
	free(prompt);
	if (!input)
	{
		data->exit_status = SUCCESS;
		return (NULL);
	}
	return (input);
}

static int	handle_history(t_data *data, char *input)
{
	add_history(input);
	if (add_history_node(&data->history, input) == -1)
	{
		free(input);
		data->exit_status = ERROR_GENERIC;
		write_stderr("Adding commands to history failed");
		return (-1);
	}
	if (save_history(&data->history, HISTORY_FILE) == -1)
	{
		data->exit_status = ERROR_GENERIC;
		free(input);
		return (-1);
	}
	return (0);
}

char	*get_commandline(t_data *data)
{
	char	*input;

	while (1)
	{
		input = retrieve_input(data);
		if (!input)
			return (NULL);
		if (no_input(input))
		{
			free(input);
			continue ;
		}
		if (handle_history(data, input) == -1)
			return (NULL);
		break ;
	}
	return (input);
}
