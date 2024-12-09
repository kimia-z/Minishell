/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:11:24 by kziari            #+#    #+#             */
/*   Updated: 2024/12/09 11:11:27 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	error_env(t_data *data, char *cmd)
{
	ft_putstr_fd("env: '", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
	data->exit_status = ERROR_GENERIC;
}

static void	error_fd(t_data *data)
{
	write_stderr("env: invalid file descriptor");
	data->exit_status = ERROR_GENERIC;
}

void	ft_env(t_command *commands, t_data *data)
{
	int		outfile;
	t_env	*temp;

	temp = data->env;
	outfile = commands->outfile_fd;
	if (outfile == -2)
		outfile = STDOUT_FILENO;
	if (outfile == -1)
		return (error_fd(data));
	if (commands->command[1])
		return (error_env(data, commands->command[1]));
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
