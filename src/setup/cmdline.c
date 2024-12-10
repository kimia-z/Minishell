/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:33:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/10 17:40:36 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"

/*
NULL for failure: lexer failure - tokenlist failure
(doesnt need data)
envp for heredoc ?
*/
t_tokenlist	*tokenizer(char **envp, char *input)
{
	t_lexer		*lexer;
	t_tokenlist	*tokenlist;

	lexer = lexer_init(input);
	if (!lexer)
		return (write_stderr("Lexer initialization failed"), NULL);
	tokenlist = tokenlist_init();
	if (!tokenlist)
	{
		lexer_free(lexer);
		return (write_stderr("Tokenlist initialization failed"), NULL);
	}
	if (lexer_main(lexer, tokenlist, envp) == -1)
	{
		write_stderr("Lexer failed");
		tokenlist_free(tokenlist);
		return (lexer_free(lexer), NULL);
	}
	lexer_free(lexer);
	return (tokenlist);
}


/*
-l on failure - tokenizer fails 
*/
int	process_cmdline(t_data *data, char *input)
{
	int	status;
	t_cmdlist	*commandlist;
	t_tokenlist	*tokenlist;

	tokenlist = tokenizer(data->envp, input);
	if (!tokenlist)
	{
		data->exit_status = ERROR_GENERIC;
		write_stderr("Lexer failed");
		return (-1);
	}
	if (syntax_checker(tokenlist) == -1)
	{
		data->exit_status = ERROR_GENERIC;
		return (tokenlist_free(tokenlist), -1);
	}
	commandlist = NULL;
	commandlist = parser(tokenlist);
	tokenlist_free(tokenlist);
	if (!commandlist)
	{
		data->exit_status = ERROR_GENERIC;
		write_stderr("Parser failed");
		return (-1);
	}
	data->commands = commandlist;
	status = ft_execute(data);
	//printf("exit code from execution: %d\n", status);
	//print_command_list(commandlist);
	free_command_list(commandlist);
	return (0); // status
}

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

/*
NULL on failure: unable to read from commandline - saving/adding to history fails - prompt failed
*/
char	*get_commandline(t_data *data)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt();
		if (!prompt)
		{
			data->exit_status = ERROR_GENERIC;
			return (write_stderr("failed to get prompt"), NULL);
		}
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			data->exit_status = SUCCESS;
			return (NULL);
		}
		if (no_input(input))
		{
			free(input);
			continue;
		}
		add_history(input);
		if (add_history_node(&data->history, input) == -1)
		{
			free(input);
			data->exit_status = ERROR_GENERIC;
			return (write_stderr("Adding commands to history failed"), NULL);
		}
		break ;
	}
	if (save_history(&data->history, HISTORY_FILE) == -1)
	{
		data->exit_status = ERROR_GENERIC;
		return (free(input), NULL);
	}
	return (input);
}