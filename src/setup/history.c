/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:19:36 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/26 13:11:09 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// TODO
// check for leaks
// check return values
// implement proper error handling

void	trim_newline(char *str)
{
	char	*newline;

	newline = ft_strchr(str, '\n');
	if (newline)
		*newline = '\0';
}

/* save history from the linked list to a file */
int	save_history(t_history *history, const char *filename)
{
	int				fd;
	t_historynode	*current;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (write_stderr("Saving commands to history file failed"), -1);
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

/* free the history linked list */
void	free_history(t_history *history)
{
	t_historynode	*next;
	t_historynode	*current;
	if (!history)
		return ;
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
	history->size = 0;
}

/*
-1 on failure: malloc fail - ft_strdup fail - no cleanup necessary from the calling function upon failure
0 on success
*/
int	add_history_node(t_history *history, const char *command)
{
	t_historynode	*new_node;
	t_historynode	*old_node;

	new_node = malloc(sizeof(t_historynode));
	if (!new_node)
		return (-1);
	new_node->command = ft_strdup(command);
	if (!new_node->command)
		return (free(new_node), -1);
	new_node->next = NULL;
	if (history->tail)
		history->tail->next = new_node;
	else
		history->head = new_node;
	history->tail = new_node;
	history->size++;
	if (history->size > HISTORY_MAX)
	{
		old_node = history->head;
		history->head = history->head->next;
		free(old_node->command);
		free(old_node);
		history->size--;
	}
	return (0);
}

/*
-1 on failure: open fails - get_next_line fails(?)
0 on success: file created successfully or/and read from
*/
int	load_history(t_history *history, const char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		fd = open(filename, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
			return (write_stderr("Failure to open history file"), -1);
		close(fd);
		return (0); 
	}
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
			return (write_stderr("Failure to populate history struct"), -1);
		}
		free(line);
	}
	close(fd);
	return (0);
}