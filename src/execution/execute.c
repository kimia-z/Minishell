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

static t_builtin	get_builtin_command(const char *cmd)
{
	if (!strcmp(cmd, "echo"))
		return (ECH);
	if (!strcmp(cmd, "cd"))
		return (CD);
	if (!strcmp(cmd, "pwd"))
		return (PWD);
	if (!strcmp(cmd, "env"))
		return (ENV);
	if (!strcmp(cmd, "export"))
		return (EXPORT);
	if (!strcmp(cmd, "unset"))
		return (UNSET);
	if (!strcmp(cmd, "exit"))
		return (EXIT);
	return (UNKNOWN);
}

bool	check_builtin(t_command *commands, t_data *data, int nb_pipes)
{
	t_builtin	cmd;

	cmd = get_builtin_command(commands->command[0]);
	if (cmd == ECH)
		return (ft_echo(commands, data), true);
	if (cmd == CD)
		return (ft_cd(commands, data), true);
	if (cmd == PWD)
		return (ft_pwd(commands, data), true);
	if (cmd == ENV)
		return (ft_env(commands, data), true);
	if (cmd == EXPORT)
		return (ft_export(commands, data), true);
	if (cmd == UNSET)
		return (ft_unset(commands, data, nb_pipes), true);
	if (cmd == EXIT)
		return (ft_exit(commands, data, nb_pipes), true);
	return (false);
}

/*
	manage the fd in pipes according to the
	command's place (first,middle,last) in pipeline
*/

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
		write_stderr("failed in dup");
		cleanup_memory_alloc(data);
		if (data->commands)
			free_command_list(data->commands);
		exit(EXIT_FAILURE);
	}
	if (check_builtin(temp, data, nb_pipes) == false)
	{
		temp->path = find_path(temp->command[0]);
		if (!temp->path)
		{
			ft_putstr_fd(temp->command[0], 2);
			ft_putendl_fd(": command not found", 2);
			// write_stderr("Command not found");
			cleanup_memory_alloc(data);
			if (data->commands)
				free_command_list(data->commands);
			exit(ERROR_GENERIC);
		}
		execve(temp->path, temp->command, data->envp);
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

void	cleanup_helper(t_data *data, char *error_msg, int exit_code)
{
	write_stderr(error_msg);
	cleanup_memory_alloc(data);
	if (data->commands)
		free_command_list(data->commands);
	exit(exit_code);
}

void	one_cmd_child(t_data *data, t_command *commands, int *pipefd)
{
	// testing
	if (signal_mode(CHILD) == -1)
	{
		perror("signal");
		//free?
		exit(EXIT_FAILURE);
	}
	// testing
	if (commands->infile_fd == -1 || commands->outfile_fd == -1)
		cleanup_helper(data, "Permission denied opening file", EXIT_FAILURE);
	if (commands->infile_fd >= 0)
	{
		if (dup2(commands->infile_fd, STDIN_FILENO) == -1)
			cleanup_helper(data, "dup2", EXIT_FAILURE);
	}
	if (commands->outfile_fd >= 0)
	{
		if (dup2(commands->outfile_fd, STDOUT_FILENO) == -1)
			cleanup_helper(data, "dup2", EXIT_FAILURE);
	}
	if (commands->redirect_in)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	if (commands->path != NULL)
		execve(commands->path, commands->command, data->envp);
	else if (commands->path == NULL)
		cleanup_helper(data, "command not found", ERROR_CMD_NOT_FOUND);
}

int	execute_one_cmd(t_data *data, t_command *commands)
{
	int	pid;
	int	status;
	int	pipefd[2];

	if (commands->redirect_in)
	{
		if (pipe(pipefd) == -1)
			return (write_stderr("failed in pipe"), ERROR_GENERIC);
		//perror
	}
	pid = fork();
	if (pid == -1)
		return (write_stderr("failed in fork"), ERROR_GENERIC);
	//perror
	if (pid == 0)
		one_cmd_child(data, commands, pipefd);
	if (commands->redirect_in)
	{
		close(pipefd[0]);
		write(pipefd[1], commands->redirect_in, strlen(commands->redirect_in));
		close(pipefd[1]);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 128;
	if (commands->infile_fd != -2)
		close(commands->infile_fd);
	if (commands->outfile_fd != -2)
		close(commands->outfile_fd);
	return (data->exit_status);
}

/*
	-start of execution
	-check the number of pipes for execution
	-call their functions and store and retuen the exit status
*/

int	ft_execute(t_data *data)
{
	int	number_pipe;

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
			data->commands->head->path = find_path(data->commands->head->command[0]);
			if (!data->commands->head->path)
			{
				write_stderr("Command not found");
				data->exit_status = ERROR_GENERIC;
				return (data->exit_status);
			}
			data->exit_status = execute_one_cmd(data, data->commands->head);
		}
	}
	else if (number_pipe >= 1)
	{
		data->exit_status = pipeline(data, number_pipe);
	}
	return (data->exit_status);
}
