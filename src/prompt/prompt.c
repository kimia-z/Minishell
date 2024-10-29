/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:08:07 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 20:48:04 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include <readline/readline.h>

//TODO
// implement ft_strcmp in libft
//check functions for errors
// check return values
// cursor movement is wacky

// NOTES
// in bash, what happens if getcwd or gethostname fail? what does minishell need to do in those cases?



// get the current working directory
static char	*get_current_working_directory()
{
	char	cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (ft_strdup("minishell> "));
	}
	return (ft_strdup(cwd));
}

// get the hostname
static char	*get_hostname()
{
	char	hostname[1024];
	if (gethostname(hostname, sizeof(hostname)) != 0)
	{
		perror("gethostname");
		return (ft_strdup("minishell> "));
	}
	return (ft_strdup(hostname));
}


static char	*build_prompt(const char *hostname, const char *cwd)
{
	char	*prompt;
	
	prompt = malloc(ft_strlen(GREEN) + ft_strlen(hostname) + ft_strlen(RESET) +
						ft_strlen(":") + ft_strlen(BLUE) + ft_strlen(cwd) + ft_strlen(RESET) +
						ft_strlen("$ ") + 1);
	if (!prompt)
	{
		perror("malloc");
		return (ft_strdup("minishell> "));
	}
	//construct_prompt();
	strcpy(prompt, GREEN);
	strcat(prompt, hostname);
	strcat(prompt, RESET);
	strcat(prompt, ":");
	strcat(prompt, BLUE);
	strcat(prompt, cwd);
	strcat(prompt, RESET);
	strcat(prompt, "$ ");
	return (prompt); // return (construct_prompt(prompt));
}


char	*get_prompt()
{
	char	*cwd;
	char	*hostname;
	char	*prompt;

	cwd = get_current_working_directory();
	hostname = get_hostname();
	prompt = build_prompt(hostname, cwd);
	free(cwd);
	free(hostname);
	return (prompt);
}