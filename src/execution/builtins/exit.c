#include "execution.h"


void	free_arrs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("str: %s\n", str[i]);
		free(str[i]);
		i++;
	}
	free(str);
}

static long long	ft_atoll(const char *str)
{
	long long	n;
	int			is_negative;

	n = 0;
	is_negative = false;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		is_negative = (*str == '-');
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		n = (n * 10) + (*str - '0');
		str++;
	}
	if (is_negative)
		return (-n);
	return (n);
}

static bool	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

/*
	first check if there is a pipe (not perform an exit)-> the command is part of a pipeline.
	no args ->simple exit, args? numeric?multiple?
	examples:
	*- exit 1000
		exit (232 (1000%256))
	*- exit 100 47 -> (did not exit)
		exit
		bash: exit: too many arguments (1)
	*- exit salam / exit salam khobi
		exit
		bash: exit: salam: numeric argument required (2)
	*- exit
		exit (0)
	*- exit | echo "kimia" -> (did not exit)
		kimia (0)
	*- exit > outfile
		exit (127)
*/

void	ft_terminate(int status, t_data *data)
{
	//unlink?
	printf("status:%d\n", data->exit_status);
	free_env_list_2(data->env);
	free(data->env);
	free_command_list(data->commands);
	free_arrs(data->envp);
	free(data);
	exit(status);
}

void	ft_exit(t_command *commands, t_data *data, int nb_pipes)
{
	if (nb_pipes > 0)
	{
		data->exit_status = SUCCESS;
		return ;
	}
	if (commands->command[0] && !commands->command[1])
	{
		ft_putstr_fd("exit\n", 2);
		data->exit_status = SUCCESS;
		ft_terminate(0, data);
	}
	if (!is_num(commands->command[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(commands->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data->exit_status = ERROR_BUILTIN_IMPROPER;
		ft_terminate(2, data);
	}
	if (commands->command[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		data->exit_status = ERROR_GENERIC;
		return ;
	}
	ft_putstr_fd("exit\n", 2);
	data->exit_status = (ft_atoll(commands->command[1]) % 256);
	ft_terminate(data->exit_status, data);
}
