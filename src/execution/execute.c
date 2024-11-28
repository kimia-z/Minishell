#include "execution.h"
#include "minishell.h"



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
	// if (!strcmp(cmd, "export"))
	// 	return (EXPORT);
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
	// if (cmd == EXPORT)
	// 	return (ft_export(commands, data), true);
	if (cmd == UNSET)
		return (ft_unset(commands, data, nb_pipes), true);
	if (cmd == EXIT)
		return (ft_exit(commands, data, nb_pipes), true);
	return (false);
}




/*
	* manage the fd in pipes according to the 
		command's place (first,middle,last) in pipeline
*/

int	ft_dup(t_command *temp, t_exe *exec, int i, int nb_pipes)
{
	if (i == 0)
	{
		if (first_pipe(temp, exec->fd) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	else if (i == nb_pipes)
	{
		if (last_pipe(temp, exec) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	else
	{
		if (middle_pipe(temp, exec) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	close(exec->fd[0]);
	close(exec->fd[1]);
	return (EXIT_SUCCESS);
}

void	ft_child(t_data *data, t_command *temp, t_exe *exec, int nb_pipes)
{
	// find/have/check path
	if (ft_dup(temp, exec, exec->i, nb_pipes) == EXIT_FAILURE)
	{
		close(exec->fd[0]);
		close(exec->fd[1]);
		if (exec->read != STDIN_FILENO)
			close (exec->read);
		//free
		write_stderr("failed in dup");
		exit(EXIT_FAILURE);
	}
	if (check_builtin(temp, data, nb_pipes) == false)
	{
		if (temp->path != NULL)
		{
			// for(int j = 0; temp->command[j]; j++)
			// {
			// 	write_stderr(temp->command[j]);
			// }
			//write_stderr(temp->path);
			execve(temp->path, temp->command, data->envp);
		}
		write_stderr("Command not found");
		//free
		exit(127);
	}
	//free
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



int	execute_one_cmd(t_data *data, t_command *commands)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		write_stderr("failed in fork");
	if (pid == 0)
	{
		if (commands->infile_fd == -1 || commands->outfile_fd == -1)
			return (EXIT_FAILURE);
		if (commands->infile_fd >= 0)
		{
			if (dup2(commands->infile_fd, STDIN_FILENO) == -1)
				return (EXIT_FAILURE);
		}
		if (commands->outfile_fd >= 0)
		{
			if (dup2(commands->outfile_fd, STDOUT_FILENO) == -1)
				return (EXIT_FAILURE);
		}
		// for (int j = 0; commands->command[j]; j++)
		// {
		// 	printf("command[%d]:%s\n", j, commands->command[j]);
		// }
		// for (int k = 0; parser->arg_env[k]; k++)
		// {
		// 	printf("arg[%d]:%s\n", k, parser->arg_env[k]);
		// }
		// printf("path:%s\n", commands->path);
		if (commands->path != NULL)
			execve(commands->path, commands->command, data->envp);
		write_stderr("Command not found");
		//free everything
		exit(127);
	}
	if (commands->infile_fd != -2)
		close (commands->infile_fd);
	if (commands->outfile_fd != -2)
		close (commands->outfile_fd);
	// if there is here doc -> unlink
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
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
	if (number_pipe == 0)
	{
		if (check_builtin(data->commands->head, data, number_pipe) == false)
		{
			// find/have/check path
			data->exit_status = execute_one_cmd(data, data->commands->head);
			//printf("status:%d\n", parser->exit_status);
			//free path
		}
	}
	else if (number_pipe >= 1)
	{
		data->exit_status = pipeline(data, number_pipe);
	}
	return (data->exit_status);
}

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	//(void)env;
// 	//test_echo();
// 	//test_pwd();
// 	//test_exit();
// 	//test_env(env);
// 	//test_unset(env);
// 	//test_cd(env);
// 	//test_pwd();
// 	//test_export(env);
// 	//test_one(env);
// 	//test_one_pipe(env);
// 	//test_two_pipe(env);
// 	return 0;
// }