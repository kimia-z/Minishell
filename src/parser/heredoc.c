/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 18:52:18 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/05 22:16:13 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// TODO
// Implement realloc
static char	*append_line_to_heredoc(char *heredoc_content, size_t *heredoc_size, const char *line, ssize_t read)
{
	heredoc_content = realloc(heredoc_content, *heredoc_size + read + 1);
	if (!heredoc_content)
	{
		perror("realloc");
		return (NULL);
	}
	ft_memcpy(heredoc_content + *heredoc_size, line, read);
	*heredoc_size += read;
	heredoc_content[*heredoc_size] = '\0';
	return (heredoc_content);
}

static char	*read_heredoc_content(const char *delimiter)
{
	char	*line;
	size_t	len;
	ssize_t	read;
	char	*heredoc_content;
	size_t	heredoc_size;

	line = NULL;
	len = 0;
	heredoc_content = NULL;
	heredoc_size = 0;
	printf("> ");
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && line[ft_strlen(delimiter)] == '\n')
			break;
		heredoc_content = append_line_to_heredoc(heredoc_content, &heredoc_size, line, read);
		if (!heredoc_content)
		{
			free(line);
			return (NULL);
		}
		printf("> ");
	}
	free(line);
	return (heredoc_content);
}

char	*handle_heredoc(const char *delimiter)
{
	char	*heredoc_content;

	if (signal_mode(HERE_DOC) == -1)
		return (NULL);
	heredoc_content = read_heredoc_content(delimiter);
	if (signal_mode(MINISHELL) == -1)
	{
		free(heredoc_content);
		return (NULL);
	}
	return (heredoc_content);
}