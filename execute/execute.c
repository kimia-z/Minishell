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
	struct s_command	commands;
	struct s_env		envs;
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
	cmd = command->tokens[0]->token->value;
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
		}
	}
	else if (number_pipe >= 1)
	{
		parser->exit_status = pipline(parser);
	}
	return (parser->exit_status);
}