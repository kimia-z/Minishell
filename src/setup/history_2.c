/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 13:30:30 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/19 14:51:42 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

static void	trim_newline(char *str)
{
	char	*newline;

	newline = ft_strchr(str, '\n');
	if (newline)
		*newline = '\0';
}

static int	read_history_from_file(t_history *history, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trim_newline(line);
		if (add_history_node(history, line) == -1)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	return (0);
}

static int	open_history_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		fd = open(filename, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
			return (-1);
		close(fd);
		return (0);
	}
	return (fd);
}

int	load_history(t_history *history, const char *filename)
{
	int	fd;

	fd = open_history_file(filename);
	if (fd <= 0)
		return (fd);
	if (read_history_from_file(history, fd) == -1)
		return (-1);
	close(fd);
	return (0);
}
