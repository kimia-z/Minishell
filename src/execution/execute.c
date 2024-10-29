#include "parser.h"

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}	t_env;


typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	char				*redirect_in;
	char				*redirect_out;
	char 				*redirect_append;
	struct s_command	*next;
}				t_command;

typedef struct s_parser
{
	int					exit_status;
	int					nb_pipes;
	int					infile_fd;
	int					outfile_fd;
	char				*infile;
	char				*outfile;
	char				*envp;
	struct s_command	*commands;
	struct s_env		*envs;
	struct s_parser		*next;
}				t_parser;

typedef enum e_builtin
{
	ECH,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
	EXIT,
	UNKNOWN
}	t_builtin;

/* start of the execution 
example: echo  "kimia" | ls |  grep  "b";
		 ----   -----    --    ----   -- 
		 tk[0]  tk[1]   tk[0]  tk[0]  tk[1]
         ------------    --    -----------
		   	cmd[0]	    cmd[1]   cmd[2]

command => tokenlist
*/

/* compare the string to builtins 
	return value: enum of type builin*/

static t_builtin	get_builtin_command(const char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECH);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (UNKNOWN);
}

bool	check_builtin(t_command *command)
{
	char	*cmd;

	// echo  "kimia" --- cmd = echo;
	//cmd = command->tokens[0]->token->value;
	if (cmd == ECH)
		return (ft_echo(command), true);
	if (cmd == CD)
		return (ft_cd(command), true);
	if (cmd == PWD)
		return (ft_pwd(command), true);
	if (cmd == ENV)
		return (ft_env(command), true);
	if (cmd == EXPORT)
		return (ft_export(command), true);
	if (cmd == UNSET)
		return (ft_unset(command), true);
	if (cmd == EXIT)
		return (ft_exit(command), true);
	return (false);
}

int	first_pipe(t_parser *parser, int *fds)
{
	if (parser->infile_fd == -1)
		return (EXIT_FAILURE);
	if (parser->infile_fd != -2)
	{
		if (dup2(parser->infile_fd, STDIN_FILENO) == -1)
		{
			return (EXIT_FAILURE);
		}
		close(parser->infile_fd);
	}
	if (parser->outfile_fd == -1)
		return(EXIT_FAILURE);
	if (parser->outfile_fd != -2)
	{
		if (dup2(parser->outfile_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	last_pipe(t_parser *parser, int *fds)
{
	if (parser->outfile_fd == -1)
		return (EXIT_FAILURE);
	if (parser->outfile_fd != -2)
	{
		if (dup2(parser->outfile_fd, STDOUT_FILENO) == -1)
		{
			return (EXIT_FAILURE);
		}
		close(parser->outfile_fd);
	}
	if (parser->infile_fd == -1)
		return(EXIT_FAILURE);
	if (parser->infile_fd != -2)
	{
		if (dup2(parser->infile_fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	middle_pipe(t_parser *parser, int *fds)
{
	if (parser->infile_fd == -1)
		return(EXIT_FAILURE);
	if (parser->infile_fd != -2)
	{
		if (dup2(parser->infile_fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	if (parser->outfile_fd == -1)
		return(EXIT_FAILURE);
	if (parser->outfile_fd != -2)
	{
		if (dup2(parser->outfile_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_dup(t_parser *parser, int *fds, int read, int i)
{
	if (i == 0)
	{
		if (first_pipe(parser, fds) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	else if (i == parser->nb_pipes)
	{
		if (last_pipe(parser, fds) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	else
	{
		if (middle_pipe(parser, fds) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	close(fds[0]);
	close(fds[1]);
	return (EXIT_SUCCESS);
}

void	ft_child(t_parser *parser, int *fds, int read, int i)
{
	// find/have/check path
	if (dup_manager(parser, fds, read, i) == EXIT_FAILURE)
	{
		close(fds[0]);
		close(fds[1]);
		if (read != STDIN_FILENO)
			close (read);
		//free
		write_stderr("failed in dup");
		exit(EXIT_FAILURE);
	}
	if (check_builtin(parser->commands) == false)
	{
		if (parser->commands->path != NULL)
		{
			execve(parser->commands->path, parser->commands, parser->envp);
			write_stderr("Command not found");
			//free
			exit(127);
		}
	}
	//free
	exit(EXIT_SUCCESS);
}


void	ft_parent(t_parser *parser, int read, int *fds)
{
	if (parser->outfile_fd != -2 && parser->outfile_fd != -1)
		close (parser->outfile_fd);
	if (parser->infile_fd != -2 && parser->infile_fd != -1)
		close (parser->infile_fd);
	close(fds[1]);
	if (read != STDIN_FILENO)
		close (read);
	//read stored in data structure?
	read = fds[0];
}

int	pipeline(t_parser *parser)
{
	int			read;
	int			fds[2];
	int			pid;
	t_command	*temp;
	int			i;
	int			status;

	read = STDIN_FILENO;
	temp = parser->commands;
	i = 0;
	while (temp != NULL)
	{
		if (pipe(fds) == -1)
			return (write_stderr("failed in pipe"), EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (write_stderr("failed in fork"), EXIT_FAILURE);
		if (pid == 0)
			ft_child(parser, fds, read, i);
		ft_parent(parser, read, fds);
		i++;
		temp = temp->next;
	}
	close (read);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		parser->exit_status = WEXITSTATUS(status);
	while (waitpid(-1, &status, 0) > 0)
	{
	}
	return (parser->exit_status);
}

int	execute_one_cmd(t_parser *parser)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		write_stderr("failed in fork");
	if (pid == 0)
	{
		if (parser->infile_fd == -1 || parser->outfile_fd == -1)
			return (EXIT_FAILURE);
		if (parser->infile_fd >= 0)
		{
			if (dup2(parser->infile_fd, STDIN_FILENO) == -1)
				return (EXIT_FAILURE);
		}
		if (parser->outfile >= 0)
		{
			if (dup2(parser->outfile_fd, STDOUT_FILENO) == -1)
				return (EXIT_FAILURE);
		}
		if (parser->commands->path != NULL)
			execve(parser->commands->path, parser->commands->command, parser->envp);
		write_stderr("Command not found");
		//free everything
		exit(127);
	}
	//if parser->infile true
	close (parser->infile_fd);
	//if parser->outfile true
	close (parser->outfile);
	// if there is here doc -> unlink
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		parser->exit_status = WEXITSTATUS(status);
	return (parser->exit_status);
}

/*
	-start of execution
	-check the number of pipes for execution
	-call their functions and store and retuen the exit status
*/

int	ft_execute(t_parser *parser)
{
	int	number_pipe;

	number_pipe = parser->nb_pipes;
	if (number_pipe == 0)
	{
		if (check_builtin(parser) == false)
		{
			// find/have/check path
			parser->exit_status = execute_one_cmd(parser);
			//free path?
		}
	}
	else if (number_pipe >= 1)
	{
		parser->exit_status = pipline(parser);
	}
	return (parser->exit_status);
}