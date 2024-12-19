/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 18:52:18 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/19 16:45:30 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

static char	*append_line_to_heredoc(char *heredoc_content, \
size_t *heredoc_size, const char *line, ssize_t read)
{
	heredoc_content = realloc(heredoc_content, *heredoc_size + read + 1);
	if (!heredoc_content)
		return (NULL);
	ft_memcpy(heredoc_content + *heredoc_size, line, read);
	*heredoc_size += read;
	heredoc_content[*heredoc_size] = '\0';
	return (heredoc_content);
}

static char	*read_line_and_check_delimiter(const char *delimiter)
{
	char	*line;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (line == NULL)
	{
		write(STDOUT_FILENO, "EOF received\n", 13);
		return (NULL);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && \
	line[ft_strlen(delimiter)] == '\n')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*append_line(char *heredoc_content, size_t *heredoc_size, \
char *line)
{
	heredoc_content = append_line_to_heredoc(heredoc_content, \
	heredoc_size, line, ft_strlen(line));
	free(line);
	if (!heredoc_content)
		return (NULL);
	return (heredoc_content);
}

static char	*read_heredoc_content(const char *delimiter)
{
	char	*line;
	char	*heredoc_content;
	size_t	heredoc_size;

	heredoc_content = NULL;
	heredoc_size = 0;
	if (signal_mode(MINISHELL) == -1)
	{
		free(heredoc_content);
		return (NULL);
	}
	while (1)
	{
		line = read_line_and_check_delimiter(delimiter);
		if (line == NULL)
			break ;
		heredoc_content = append_line(heredoc_content, &heredoc_size, line);
		if (!heredoc_content)
			return (NULL);
	}
	return (heredoc_content);
}

int	handle_heredoc(const char *delimiter)
{
	char	*heredoc_content;
	int		temp_fd;
	char	*temp_filename;

	temp_filename = "/tmp/hredoc_temp.txt";
	if (signal_mode(HERE_DOC) == -1)
		return (-1);
	heredoc_content = read_heredoc_content(delimiter);
	if (heredoc_content == NULL)
		return (-1);
	temp_fd = open(temp_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		free(heredoc_content);
		return (-1);
	}
	write(temp_fd, heredoc_content, ft_strlen(heredoc_content));
	free(heredoc_content);
	close(temp_fd);
	temp_fd = open(temp_filename, O_RDWR);
	if (temp_fd == -1)
		return (-1);
	return (temp_fd);
}
