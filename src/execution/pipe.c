#include "execution.h"
#include "minishell.h"


int	pipe_count(t_cmdlist *commands)
{
	t_command	*temp;
	int			nb_pipe;

	temp = commands->head;
	nb_pipe = 0;
	while (temp->next != NULL)
	{
		nb_pipe++;
		temp = temp->next;
	}
	return (nb_pipe);
}


int	last_pipe(t_command *temp, t_exe *exec)
{
	if (temp->outfile_fd != -2)
	{
		if (dup2(temp->outfile_fd, STDOUT_FILENO) == -1)
		{
			return (EXIT_FAILURE);
		}
	}
	if (temp->infile_fd == -1)
		return(EXIT_FAILURE);
	if (temp->infile_fd != -2)
	{
		if (dup2(temp->infile_fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(temp->infile_fd);
	}
	else
	{
		if (dup2(exec->read, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(exec->read);
	}
	return (EXIT_SUCCESS);
}

int	middle_pipe(t_command *temp, t_exe *exec)
{
	if (temp->infile_fd == -1)
		return(EXIT_FAILURE);
	if (temp->infile_fd != -2)
	{
		if (dup2(temp->infile_fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(temp->infile_fd);
	}
	else
	{
		if (dup2(exec->read, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		close(exec->read);
	}
	if (temp->outfile_fd != -2)
	{
		if (dup2(temp->outfile_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(exec->fd[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	first_pipe(t_command *temp, int *fds)
{
	if (temp->infile_fd == -1)
		return (EXIT_FAILURE);
	if (temp->infile_fd != -2)
	{
		if (dup2(temp->infile_fd, STDIN_FILENO) == -1)
		{
			return (EXIT_FAILURE);
		}
		close(temp->infile_fd);
	}
	if (temp->outfile_fd != -2)
	{
		if (dup2(temp->outfile_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		//write_stderr("before");
		if (dup2(fds[1], STDOUT_FILENO) == -1) {
			//write_stderr("in");
			return (EXIT_FAILURE);
		}
		//write_stderr("after");
	}
	return (EXIT_SUCCESS);
}


int	pipeline(t_data *data, int nb_pipes)
{
	t_exe		exec;
	t_command	*temp;

	exec.read = STDIN_FILENO;
	temp = data->commands->head;
	exec.i = 0;
	while (temp != NULL)
	{
		if (pipe(exec.fd) == -1)
			return (write_stderr("failed in pipe"), EXIT_FAILURE);
		exec.pid = fork();
		if (exec.pid == -1)
			return (write_stderr("failed in fork"), EXIT_FAILURE);
		if (exec.pid == 0)
			ft_child(data, temp, &exec, nb_pipes);
		ft_parent(temp, &exec);
		exec.i++;
		temp = temp->next;
	}
	close (exec.read);
	waitpid(exec.pid, &exec.status, 0);
	if (WIFEXITED(exec.status))
		data->exit_status = WEXITSTATUS(exec.status);
	while (waitpid(-1, &exec.status, 0) > 0)
	{
	}
	return (data->exit_status);
}
