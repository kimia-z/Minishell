/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 18:52:18 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/10 23:55:21 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// TODO
// Implement realloc

static char	*append_line_to_heredoc(char *heredoc_content, size_t \
*heredoc_size, const char *line, ssize_t read)
{
	heredoc_content = realloc(heredoc_content, *heredoc_size + read + 1);
	if (!heredoc_content)
	{
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
	
	if (signal_mode(MINISHELL) == -1)
	{
		free(heredoc_content);
		return (NULL);
	}
	
	write(STDOUT_FILENO, "> ", 2);
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
		write(STDOUT_FILENO, "> ", 2);
	}
	free(line);
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
	temp_fd = open(temp_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		free(heredoc_content);
		return (-1);
	}
	write(temp_fd, heredoc_content, ft_strlen(heredoc_content));
	free(heredoc_content);
	//lseek(temp_fd, 0, SEEK_SET); //replace
	close(temp_fd);
	temp_fd = open(temp_filename, O_RDWR);
	if (temp_fd == -1)
		return (-1);
	return (temp_fd);
}
