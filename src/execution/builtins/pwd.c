#include "execution.h"

/*
This function is doing the pwd builtin
	* What should it do when pwd variable was not found?
error check for getcwd
fail scenarios:
	- getcwd fails
	-invalid arguments
*/
int	ft_pwd(t_command *commands, t_data *data)
{
	int		outfile;
	char	*current_directory_path;

	if (!commands->command[0])
		return (1);
	if (commands->command[0] && !commands->command[1])
	{
		current_directory_path = getcwd(NULL, 0);
		if (!current_directory_path)
			return (-1);
		outfile = commands->outfile_fd;
		if (outfile == -2)
			outfile = STDOUT_FILENO;
		ft_putendl_fd(current_directory_path, outfile);
		free(current_directory_path);
		data->exit_status = 0;
	}
	if (commands->command[1])
	{
		if (!ft_strncmp(commands->command[1], "--", 2) || *(commands->command[1]) == '-')
			//ft_putstr("pwd: bad option: -\n");
			ft_putendl_fd("pwd: bad option: -", outfile);
		else
		ft_putendl_fd("pwd: too many arguments", outfile);
			//ft_putstr("pwd: too many arguments\n");
		data->exit_status = ERROR_GENERIC;
		return (-1);
	}
	return (0);
}