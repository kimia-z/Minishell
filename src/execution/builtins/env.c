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
	// if (!parser || !data->env)
	// {
	// 	return(ft_putstr_fd("Error: no env variables available\n", 2));
	// }
	if (commands->command[1])
	{
		printf("env: '%s': No such file or directory\n", commands->command[1]);
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
	data->exit_status = 0;
}
