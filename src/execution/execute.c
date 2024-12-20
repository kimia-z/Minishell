/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kziari <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/11 13:17:40 by kziari        #+#    #+#                 */
/*   Updated: 2024/12/19 17:06:47 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	manage the fd in pipes according to the
	command's place (first,middle,last) in pipeline
*/

static int	path_helper(t_data *data)
{
	t_command	*head;

	head = data->commands->head;
	head->path = find_path(data->commands->head->command[0]);
	if (!data->commands->head->path)
	{
		ft_putstr_fd(data->commands->head->command[0], 2);
		ft_putendl_fd(": command not found", 2);
		data->exit_status = ERROR_GENERIC;
		return (-1);
	}
	return (0);
}

int	ft_dup(t_command *temp, t_exe *exec, int i, int nb_pipes)
{
	if (i == 0)
	{
		if (first_pipe(temp, exec->fd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (i == nb_pipes)
	{
		if (last_pipe(temp, exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (middle_pipe(temp, exec) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	close(exec->fd[0]);
	close(exec->fd[1]);
	return (EXIT_SUCCESS);
}

void	ft_child(t_data *data, t_command *temp, t_exe *exec, int nb_pipes)
{
	if (ft_dup(temp, exec, exec->i, nb_pipes) == EXIT_FAILURE)
	{
		close(exec->fd[0]);
		close(exec->fd[1]);
		if (exec->read != STDIN_FILENO)
			close (exec->read);
		cleanup_helper(data, "dup2 failed", EXIT_FAILURE);
	}
	if (check_builtin(temp, data, nb_pipes) == false)
	{
		temp->path = find_path(temp->command[0]);
		if (temp->path)
			execve(temp->path, temp->command, data->envp);
		ft_putstr_fd(temp->command[0], 2);
		ft_putendl_fd(": command not found", 2);
		cleanup_memory_alloc(data);
		if (data->commands)
			free_command_list(data->commands);
		exit(ERROR_CMD_NOT_FOUND);
	}
	cleanup_memory_alloc(data);
	if (data->commands)
		free_command_list(data->commands);
	exit(EXIT_SUCCESS);
}

void	ft_parent(t_command *temp, t_exe *exec)
{
	if (temp->outfile_fd != -2 && temp->outfile_fd != -1)
		close (temp->outfile_fd);
	if (temp->infile_fd != -2 && temp->infile_fd != -1)
		close (temp->infile_fd);
	close(exec->fd[1]);
	if (exec->read != STDIN_FILENO)
		close (exec->read);
	exec->read = exec->fd[0];
}

/*
	-start of execution
	-check the number of pipes for execution
	-call their functions and store and retuen the exit status
*/

int	ft_execute(t_data *data)
{
	int			number_pipe;

	number_pipe = pipe_count(data->commands);
	if (!data->commands->head->command)
	{
		data->exit_status = SUCCESS;
		return (data->exit_status);
	}
	if (number_pipe == 0)
	{
		if (check_builtin(data->commands->head, data, number_pipe) == false)
		{
			if (path_helper(data) == -1)
				return (data->exit_status);
			data->exit_status = execute_one_cmd(data, data->commands->head);
		}
	}
	else if (number_pipe >= 1)
	{
		data->exit_status = pipeline(data, number_pipe);
	}
	return (data->exit_status);
}
