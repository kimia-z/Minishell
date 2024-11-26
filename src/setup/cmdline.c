/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:33:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/26 17:59:13 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//TODO

// ctl c doesnt work for termination in do_things
// implement ft_strcmp in libft
//check functions for errors
// check return values
// prompt doesnt print after ctrl c 
// ISSUE: CTR C doesnt give you back the prompt - fix it


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
	if (lexer_main(lexer, tokenlist) == -1)
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
	//int	status; //to track exit code
	t_cmdlist	*commandlist;
	t_tokenlist	*tokenlist;

	tokenlist = tokenizer(data->envp, input);
	if (!tokenlist)
		return (-1);
	if (syntax_checker(tokenlist) == -1)
		return (tokenlist_free(tokenlist), -1);
	commandlist = NULL;
	commandlist = parser(tokenlist);
	tokenlist_free(tokenlist);
	if (!commandlist)
	{
		write_stderr("Parser failed miserably.");
		return (-1);
	}	
	//status = ft_execute(data, commandlist);

	print_command_list(commandlist);
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
			return (write_stderr("failed to get prompt"), NULL);
		input = readline(prompt);
		free(prompt);
		if (!input)
			return (NULL);
		if (no_input(input))
		{
			free(input);
			continue;
		}
		add_history(input);
		if (add_history_node(&data->history, input) == -1)
		{
			free(input); // right placement?
			return (write_stderr("Adding commands to history failed"), NULL);
		}
		break ; //is this break properly placed?
	}
	if (save_history(&data->history, HISTORY_FILE) == -1)
		return (free(input), NULL);
	return (input);
}