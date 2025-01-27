/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kziari <kziari@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 11:18:27 by kziari        #+#    #+#                 */
/*   Updated: 2024/12/23 13:09:22 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	first check if there is a pipe (not perform an exit)->
	the command is part of a pipeline.
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

#include "execution.h"

static void	exit_helper(t_data *data, char *cmd)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	data->exit_status = ERROR_BUILTIN_IMPROPER;
}

static long long	ft_atoll(const char *str)
{
	long long	n;
	bool		is_negative;

	n = 0;
	is_negative = false;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_negative = true;
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
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_terminate(int status, t_data *data)
{
	cleanup_memory_alloc(data);
	if (data->commands)
		free_command_list(data->commands);
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
		exit_helper(data, commands->command[1]);
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
