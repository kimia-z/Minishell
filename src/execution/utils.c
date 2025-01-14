/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kziari <kziari@42.fr>                        +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:12:36 by kziari        #+#    #+#                 */
/*   Updated: 2024/12/23 14:29:15 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_builtin	get_builtin_command(const char *cmd)
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
	if (cmd == EXPORT)
		return (ft_export(commands, data), true);
	if (cmd == UNSET)
		return (ft_unset(commands, data, nb_pipes), true);
	if (cmd == EXIT)
		return (ft_exit(commands, data, nb_pipes), true);
	return (false);
}

void	cleanup_helper(t_data *data, char *error_msg, int exit_code)
{
	write_stderr(error_msg);
	cleanup_memory_alloc(data);
	if (data->commands)
		free_command_list(data->commands);
	exit(exit_code);
}

void	status_handler(t_data *data, int status)
{
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 128;
}

void	wait_helper(t_exe *exec)
{
	while (waitpid(-1, &exec->status, 0) > 0)
	{
	}
}
