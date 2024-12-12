/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:12:36 by kziari            #+#    #+#             */
/*   Updated: 2024/12/12 14:12:37 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	status_handler(t_data *data, t_exe *exec)
{
	if (WIFEXITED(exec->status))
		data->exit_status = WEXITSTATUS(exec->status);
	else if (WIFSIGNALED(exec->status))
		data->exit_status = WTERMSIG(exec->status) + 128;
}

void	wait_helper(t_exe *exec)
{
	while (waitpid(-1, &exec->status, 0) > 0)
	{
	}
}
