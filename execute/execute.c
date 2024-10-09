#include "parser.h"

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

/* it will execute the command with its path
	-finding paths
	-*/

void	run_path_cmd(t_command *command)
{

}

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

/* check the first token of the commad
	if it is a builtin call its function to execute
	if not call the function to execute with its path
	return value: undefined(maybe it should be the exit status with
	return value of the builtins function or exit status that stored
	with waitpid in path commands)*/

void	check_builtin(t_command *command)
{
	char	*cmd;

	// echo  "kimia" --- cmd = echo;
	cmd = command->tokens[0]->token->value;
	if (cmd == ECH)
		return (ft_echo(command));
	if (cmd == CD)
		return (ft_cd(command));
	if (cmd == PWD)
		return (ft_pwd(command));
	if (cmd == ENV)
		return (ft_env(command));
	if (cmd == EXPORT)
		return (ft_export(command));
	if (cmd == UNSET)
		return (ft_unset(command));
	if (cmd == EXIT)
		return (ft_exit(command));
	return (run_path_cmd(command));
}

/* start of the execution 
	loop through the commands and call the function to 
	check if it is builtin or not and execute them
	return value: undefined */

void	ft_execute(t_command *commands)
{
	t_command	*temp;

	temp = commands;
	while (temp->command)
	{
		check_builtin(temp->command);
		temp->command = temp->command->next;
	}
}