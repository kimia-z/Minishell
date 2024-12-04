#include "execution.h"
#include "minishell.h"

void	ft_env(t_command *commands, t_data *data)
{
	int		outfile;
	t_env	*temp;

	temp = data->env;
	outfile = commands->outfile_fd;
	if (outfile == -2)
		outfile = STDOUT_FILENO;
	if (outfile < 0)
	{
		ft_putstr_fd("env: invalid file descriptor\n", STDERR_FILENO);
		data->exit_status = ERROR_GENERIC;
		return ;
	}
	if (commands->command[1])
	{

		ft_putstr_fd("env: '", STDERR_FILENO);
        ft_putstr_fd(commands->command[1], STDERR_FILENO);
        ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
        data->exit_status = ERROR_GENERIC;
        return ;
	}
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr_fd(temp->key, outfile);
			ft_putchar_fd('=', outfile);
			ft_putendl_fd(temp->value, outfile);
		}
		temp = temp->next;
	}
	data->exit_status = SUCCESS;
}
