/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   one_cmd.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: kziari <marvin@42.fr>                         +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/19 17:23:13 by kziari         #+#    #+#                */
/*   Updated: 2024/12/19 17:23:14 by kziari         ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	close_helper(int *pipefd, char *redirect_in)
{
	close(pipefd[0]);
	write(pipefd[1], redirect_in, strlen(redirect_in));
	close(pipefd[1]);
}

static void	one_cmd_child(t_data *data, t_command *commands, int *pipefd)
{
	if (signal_mode(CHILD) == -1)
		cleanup_helper(data, "signal failed", EXIT_FAILURE);
	if (commands->infile_fd == -1 || commands->outfile_fd == -1)
		cleanup_helper(data, "Permission denied opening file", EXIT_FAILURE);
	if (commands->infile_fd >= 0)
	{
		if (dup2(commands->infile_fd, STDIN_FILENO) == -1)
			cleanup_helper(data, "dup2 failed", EXIT_FAILURE);
	}
	if (commands->outfile_fd >= 0)
	{
		if (dup2(commands->outfile_fd, STDOUT_FILENO) == -1)
			cleanup_helper(data, "dup2 failed", EXIT_FAILURE);
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
	}
	pid = fork();
	if (pid == -1)
		return (write_stderr("failed in fork"), ERROR_GENERIC);
	if (pid == 0)
		one_cmd_child(data, commands, pipefd);
	if (commands->redirect_in)
		close_helper(pipefd, commands->redirect_in);
	waitpid(pid, &status, 0);
	status_handler(data, status);
	if (commands->infile_fd != -2)
		close(commands->infile_fd);
	if (commands->outfile_fd != -2)
		close(commands->outfile_fd);
	return (data->exit_status);
}
