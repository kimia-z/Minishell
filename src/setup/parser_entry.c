/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_entry.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 21:00:50 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/24 20:02:18 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// cmd->infile_fd = -2 && cmd->outfile_fd = -2 are the flag for when we do not have a redirect
// it seems you are mallocing here and also in parse_command function


// static t_command *cmd_init()
// {
// 	//I think this memory allocating is not nessecary!!!!!
// 	//t_command *cmd = NULL;
// 	t_command *cmd = (t_command *)malloc(sizeof(t_command));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->command = NULL;
// 	//cmd->command = NULL;
// 	cmd->path = NULL;
// 	// cmd->args = NULL;
// 	cmd->redirect_in = NULL;
// 	cmd->redirect_out = NULL;
// 	cmd->redirect_append = NULL;
// 	cmd->next = NULL;
// 	cmd->infile_fd = -2;
// 	cmd->outfile_fd = -2;
// 	return (cmd);
// }

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

// int	parser(t_data *data, char *input)
// {
// 	t_tokenlist	*tokenlist;
// 	t_parser	*parser;
// 	t_command	*cmdlist;

	
// 	parser = parser_init(tokenlist); //malloced
// 	if (!parser)
// 		return -1;
	
// 	//data->parser = parser; //deosnt need it
// 	// cmdlist = cmd_init();
// 	// if (!cmdlist)
// 	// 	return -1;
// 	//data->cmdlist = cmdlist;
// 	cmdlist = parse(parser, tokenlist);
// 	if (!cmdlist)
// 		return (-1); // parsing error - path not found - lethal -dont print error, already handled
// 	//print_command_list(cmdlist);
// 	tokenlist_free(tokenlist);
// 	free(parser);
// 	free_command_list(cmdlist);
// 	return (0);
// }

t_cmdlist	*cmdlist_init()
{
	t_cmdlist	*cmdlist;

	cmdlist = malloc(sizeof(t_cmdlist));
	if (!cmdlist)
		return (NULL);
	ft_bzero(cmdlist, sizeof(t_cmdlist));
	cmdlist->num_commands = 0;
	cmdlist->head = NULL;
	return (cmdlist);
}

t_cmdlist	*parser(t_tokenlist *tokenlist)
{

	t_command *last_command;
	t_command *current_command;
	t_cmdlist *cmdlist;
	t_token *current_token;

	last_command = NULL;
	current_token = tokenlist->head;
	cmdlist = cmdlist_init();
	if (!cmdlist)
		return (NULL);
	while (current_token != NULL)
	{
		current_command = parse_command(&current_token);
		if (!current_command)
		{
			//free_command_list(cmdlist);
			return (NULL); // lethal
		}
		if (!cmdlist->head) // first command
			cmdlist->head = current_command;
		else
			last_command->next = current_command;
		cmdlist->num_commands++;
		last_command = current_command;
		if (current_token && is_pipe(current_token->type))
			//advance_token(parser);
			current_token = current_token->next;
	}
	return (cmdlist);
}




// int	parser(t_tokenlist *tokenlist)
// {
// 	t_cmdlist	*cmdlist;

// 	cmdlist = cmdlist_init();
// 	if (!cmdlist)
// 		return (-1);
// 	if (parser_main(cmdlist, tokenlist) == -1)
// 	{
// 		parser_free();
// 		write_stderr();
// 		return (-1);
// 	}

// 	tokenlist_free(tokenlist);

// 	free_command_list(cmdlist);
// 	return (0);
// }