#include "execution.h"

/*
This function is doing the pwd builtin
	* What should it do when pwd variable was not found?
error check for getcwd
fail scenarios:
	- getcwd fails
	-invalid arguments
*/
void	ft_pwd(t_command *commands, t_data *data)
{
	int		outfile;
	char	*current_directory_path;

	//how commands->command[0] could be NULL?
	// if (!commands->command[0])
	// 	return (1);
	current_directory_path = getcwd(NULL, 0);
	if (!current_directory_path)
	{
		data->exit_status = ERROR_GENERIC;
		return ;
	}
	outfile = commands->outfile_fd;
	if (outfile == -2)
		outfile = STDOUT_FILENO;
	ft_putendl_fd(current_directory_path, outfile);
	free(current_directory_path);
	data->exit_status = SUCCESS;
}
