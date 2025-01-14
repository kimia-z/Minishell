/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   one_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kziari <marvin@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 17:23:13 by kziari        #+#    #+#                 */
/*   Updated: 2024/12/23 14:25:43 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	close_helper(int *pipefd, char *redirect_in)
{
	close(pipefd[0]);
	write(pipefd[1], redirect_in, ft_strlen(redirect_in));
	close(pipefd[1]);
}

static void	handle_fd(int src_fd, int dest_fd, t_data *data, char *error_msg)
{
	if (src_fd >= 0)
	{
		if (dup2(src_fd, dest_fd) == -1)
			cleanup_helper(data, error_msg, EXIT_FAILURE);
		close(src_fd);
	}
}

static void	one_cmd_child(t_data *data, t_command *commands, int *pipefd)
{
	if (signal_mode(CHILD) == -1)
		cleanup_helper(data, "signal failed", EXIT_FAILURE);
	if (commands->infile_fd == -1 || commands->outfile_fd == -1)
		cleanup_helper(data, "Permission denied opening file", EXIT_FAILURE);
	handle_fd(commands->infile_fd, STDIN_FILENO, data, "dup2 failed");
	if (commands->infile_fd < 0 && pipefd != NULL && pipefd[0] >= 0)
	{
		close(pipefd[1]);
		handle_fd(pipefd[0], STDIN_FILENO, data, "dup2 failed for pipe");
	}
	handle_fd(commands->outfile_fd, STDOUT_FILENO, data, "dup2 failed");
	if (commands->path != NULL)
		execve(commands->path, commands->command, data->envp);
	cleanup_helper(data, "command not found", ERROR_CMD_NOT_FOUND);
}

int	execute_one_cmd(t_data *data, t_command *commands)
{
	int	pid;
	int	status;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (write_stderr("failed in pipe"), ERROR_GENERIC);
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
