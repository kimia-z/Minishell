/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:04:44 by kziari            #+#    #+#             */
/*   Updated: 2024/12/08 17:04:49 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	This function is doing the pwd builtin
*/
void	ft_pwd(t_command *commands, t_data *data)
{
	int		outfile;
	char	*current_directory_path;

	outfile = commands->outfile_fd;
	if (outfile == -1)
	{
		write_stderr("pwd: invalid file descriptor");
		data->exit_status = ERROR_GENERIC;
		return ;
	}
	if (outfile == -2)
		outfile = STDOUT_FILENO;
	current_directory_path = getcwd(NULL, 0);
	if (!current_directory_path)
	{
		ft_putendl_fd("pwd: getcwd() failed", 2);
		data->exit_status = ERROR_GENERIC;
		return ;
	}
	ft_putendl_fd(current_directory_path, outfile);
	free(current_directory_path);
	data->exit_status = SUCCESS;
}
