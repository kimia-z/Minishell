/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:19:36 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 13:55:03 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// TODO
// check load_history for leaks
// check return values

// NOTES
// history is loaded from a file - read and loaded from a file
// have history as a linked list for immediate access and then write off to a file later
// if we decided to save history to a file we could use these fuctions


// save history from the linked list to a file
int	save_history(t_history *history, const char *filename)
{
	int				fd;
	t_historynode	*current;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	current = history->head;
	while (current)
	{
		ft_putstr_fd(current->command, fd);
		write(fd, "\n", 1);
		current = current->next;
	}
	close(fd);
	return (0);
}

// free the history linked list
void	free_history(t_history *history)
{
	t_historynode	*next;
	t_historynode	*current;

	current = history->head;
	while (current)
	{
		next = current->next;
		free(current->command);
		free(current);
		current = next;
	}
	history->head = NULL;
	history->tail = NULL;
}


int	add_history_node(t_history *history, const char *command)
{
	t_historynode	*new_node;

	new_node = malloc(sizeof(t_historynode));
	if (!new_node)
		return (-1);
	new_node->command = ft_strdup(command);
	if (!new_node->command)
		return (-1);
	new_node->next = NULL;
	if (history->tail)
		history->tail->next = new_node;
	else
		history->head = new_node;
	history->tail = new_node;
}


int	load_history(t_history *history, const char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		add_history_node(history, line);
		add_history(line);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}