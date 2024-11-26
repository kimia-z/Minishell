/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 14:08:07 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/26 18:38:01 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

//TODO
//check functions for errors
// check return values
// cursor movement is wacky - not necessary

// NOTES
// in bash, what happens if getcwd or gethostname fail? what does minishell need to do in those cases?



/* get the current working directory */
static char	*get_current_working_directory()
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		write_stderr("getcwd failed");
		return (ft_strdup(PROMPT_DEFAULT));
	}
	return (ft_strdup(cwd));
}

/* get the hostname */
static char	*get_hostname()
{
	char	hostname[1024];

	if (gethostname(hostname, sizeof(hostname)) != 0)
	{
		write_stderr("gethostname failed");
		return (ft_strdup(PROMPT_DEFAULT));
	}
	return (ft_strdup(hostname));
}

static void	append_to_prompt(char *prompt, size_t prompt_len, const char *str)
{
	ft_strlcat(prompt, str, prompt_len);
}

static char	*build_prompt(const char *hostname, const char *cwd)
{
	char	*prompt;
	size_t	prompt_len;

	prompt_len = ft_strlen(GREEN) + ft_strlen(hostname) + ft_strlen(RESET) +
				ft_strlen(":") + ft_strlen(BLUE) + ft_strlen(cwd) + ft_strlen(RESET) +
				ft_strlen("$ ") + 1;
	prompt = malloc(prompt_len);
	if (!prompt)
	{
		write_stderr("malloc failed");
		return (ft_strdup(PROMPT_DEFAULT));
	}
	prompt[0] = '\0';
	append_to_prompt(prompt, prompt_len, GREEN);
	append_to_prompt(prompt, prompt_len, hostname);
	append_to_prompt(prompt, prompt_len, RESET);
	append_to_prompt(prompt, prompt_len, ":");
	append_to_prompt(prompt, prompt_len, BLUE);
	append_to_prompt(prompt, prompt_len, cwd);
	append_to_prompt(prompt, prompt_len, RESET);
	append_to_prompt(prompt, prompt_len, "$ ");
	return (prompt);
}

char	*get_prompt()
{
	char *cwd;
	char *hostname;
	char *prompt;

	cwd = get_current_working_directory();
	if (!cwd)
		return (ft_strdup(PROMPT_DEFAULT));
	hostname = get_hostname();
	if (!hostname)
	{
		free(cwd);
		return (ft_strdup(PROMPT_DEFAULT));
	}
	prompt = build_prompt(hostname, cwd);
	free(cwd);
	free(hostname);
	if (!prompt)
		return (ft_strdup(PROMPT_DEFAULT));
	return (prompt);
}