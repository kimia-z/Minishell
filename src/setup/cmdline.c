/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:33:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/24 20:01:11 by yasamankari   ########   odam.nl         */
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

int	process_cmdline(t_data *data, char *input)
{
	//int	status; //to track exit code
	t_cmdlist	*commandlist;
	t_tokenlist	*tokenlist;

	tokenlist = tokenizer(data->envp, input);
	if (!tokenlist)
		return (-1);
	if (syntax_checker(tokenlist) == -1)
	{
		tokenlist_free(tokenlist);
		return -1;
	}
	commandlist = parser(tokenlist);
	if (!commandlist)
	{
		printf("oops\n");
		//handle error
	}	
	//status = ft_execute(data, commandlist);
	// error check
	//cleanup regarding parser if any
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
NULL on failure: unable to read from commandline - saving/adding to history fails
*/
char	*get_commandline(t_data *data)
{
	char	*input;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt();
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