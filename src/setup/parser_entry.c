/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_entry.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 21:00:50 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/19 23:04:47 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// cmd->infile_fd = -2 && cmd->outfile_fd = -2 are the flag for when we do not have a redirect
// it seems you are mallocing here and also in parse_command function


static t_command *cmd_init()
{
	//I think this memory allocating is not nessecary!!!!!
	//t_command *cmd = NULL;
	t_command *cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command = NULL;
	//cmd->command = NULL;
	cmd->path = NULL;
	// cmd->args = NULL;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->redirect_append = NULL;
	cmd->next = NULL;
	cmd->infile_fd = -2;
	cmd->outfile_fd = -2;
	return (cmd);
}

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
	//data->lexer = lexer;
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

int	parser_entry(t_data *data, char *input)
{
	t_tokenlist	*tokenlist;
	t_parser	*parser;
	t_command	*cmdlist;

	
	
	parser = parser_init(tokenlist); //malloced
	if (!parser)
		return -1;
	//data->parser = parser; //deosnt need it
	// cmdlist = cmd_init();
	// if (!cmdlist)
	// 	return -1;
	//data->cmdlist = cmdlist;
	cmdlist = parse(parser, tokenlist);
	if (!cmdlist)
		return (-1); // parsing error - path not found - lethal -dont print error, already handled
	//print_command_list(cmdlist);
	tokenlist_free(tokenlist);
	free(parser);
	free_command_list(cmdlist);
	return (0);
}
