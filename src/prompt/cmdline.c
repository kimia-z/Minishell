/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 21:00:50 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/30 18:25:17 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//TODO
//better names for functions(esp parser)

//NOTES


// getline allocates with malloc. free when you're done
/*  readline  returns  the text of the line read.  A blank line returns the
	   empty string.  If EOF is encountered while reading a line, and the line
	   is  empty,  NULL is returned.  If an EOF is read with a non-empty line,
	   it is treated as a newline.
*/



/*
	lexer 
	parser
	executor
	preliminary cleanup if needed
*/
// void process_commandline(char *input)
// {
//     printf("Executing: %s\n", input);
//     data->lexer = lexer(data, line);
//     if ()
//         return ;
//     data->parser = parser();
//     if ()
//         return ; // or assign error
//     executor();
//     free things;
//     tokenlist_free(tokenlist);
// 	free(parser);
// 	free_command_list(cmdlist);
//     return ();
// }

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



t_tokenlist *tokenizer(t_data *data, char *input)
{
	t_lexer 	*lexer;
	t_tokenlist	*tokenlist;
	//char		*input;


	//input = "echo hello | ls > out | wc -l";
	lexer = lexer_init(input);
	if (!lexer)
		return (NULL);
	data->lexer = lexer;
	tokenlist = tokenlist_init();
	lexer_process_input(lexer, tokenlist);
	lexer_free(lexer);
	return (tokenlist);
}

/*
	!!!! data->cmdlist always would be empty !!!!!
	data->cmdlist = cmdlist;
	cmdlist = parse(parser, tokenlist);
*/

int	parser(t_data *data, char *input)
{
	t_tokenlist	*tokenlist;
	t_parser *parser;
	t_command *cmdlist;

	tokenlist = tokenizer(data, input);
	if (!tokenlist)
		return -1;
	//return (ft_perror(malloc_error), -1); // malloc error - lethal
	parser = parser_init(tokenlist);
	if (!parser)
		return -1;
	//return (ft_perror(malloc_error), -1); // mallloc error - lethal
	data->parser = parser;
	cmdlist = cmd_init();
	if (!cmdlist)
		return -1;
	//return (ft_perror(malloc_error), -1); // malloc error - lethal
	data->cmdlist = cmdlist;
	cmdlist = parse(parser, tokenlist);
	if (!cmdlist)
		return (-1); // syntax error - parsing error - path not found - lethal -dont print error, already handled
	tokenlist_free(tokenlist);
	free(parser);
	//ft_execute(data, cmdlist);
	free_command_list(cmdlist);
	return (0);
}



//void process_commandline(t_data *data, char *input)
//{
	//t_lexer 	*lexer;
	//t_tokenlist	*tokenlist;
	//char		*input;
	//t_parser *parser;
	//t_command *commandlist;



	//commandlist = parser(data, input);



	//input = get_line();
	//printf("input is:%s\n", input);
	//free(input);

	//input = "echo hello | ls > out | wc -l";
	//lexer = lexer_init(input);
	//data->lexer = lexer;
	//printf("inside smd, input: %s\n", lexer->input);
	//tokenlist = tokenlist_init();
	//data->tokenlist = tokenlist;

	// lexer_process_input(lexer, tokenlist);
	// tokenlist_print(tokenlist->head);
	// parser = parser_init(tokenlist);
	// data->parser = parser;

	// cmdlist = cmd_init();
	// data->cmdlist = cmdlist;
	// cmdlist = parse(parser, tokenlist);
	//print_command_list(cmdlist);
	//printf("\n\n");
	//execute();
	//lexer_free(lexer);
	// tokenlist_free(tokenlist);
	// free(parser);
	//free_command_list(commandlist);
	
	//return (0);
//}
