/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline_2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 13:04:10 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/19 14:49:25 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"

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

static t_tokenlist	*tokenize_input(t_data *data, char *input)
{
	t_tokenlist	*tokenlist;

	tokenlist = tokenizer(data->envp, input);
	if (!tokenlist)
	{
		data->exit_status = ERROR_GENERIC;
		write_stderr("Lexer failed");
		return (NULL);
	}
	return (tokenlist);
}

static int	check_syntax(t_data *data, t_tokenlist *tokenlist)
{
	if (syntax_checker(tokenlist) == -1)
	{
		data->exit_status = ERROR_GENERIC;
		write_stderr("Not found");
		tokenlist_free(tokenlist);
		return (-1);
	}
	return (0);
}

static t_cmdlist	*parse_tokens(t_data *data, t_tokenlist *tokenlist)
{
	t_cmdlist	*commandlist;

	commandlist = parser(tokenlist);
	tokenlist_free(tokenlist);
	if (!commandlist)
	{
		data->exit_status = ERROR_GENERIC;
		write_stderr("Parser failed");
		return (NULL);
	}
	return (commandlist);
}

int	process_cmdline(t_data *data, char *input)
{
	int			status;
	t_tokenlist	*tokenlist;
	t_cmdlist	*commandlist;

	tokenlist = tokenize_input(data, input);
	if (!tokenlist)
		return (-1);
	if (check_syntax(data, tokenlist) == -1)
		return (-1);
	commandlist = parse_tokens(data, tokenlist);
	if (!commandlist)
		return (-1);
	data->commands = commandlist;
	status = ft_execute(data);
	free_command_list(commandlist);
	return (status);
}
