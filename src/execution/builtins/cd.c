/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:59:26 by kziari            #+#    #+#             */
/*   Updated: 2024/12/09 10:59:29 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
/*
	If no directory argument is provided, it changes to the `HOME` dir.
	if HOME is not availabe, print error
	If more than one argument is provided, -> error).
	validation of the directory provided
	-permissions fot the directory are met - fixed
	relative path - yes
	-absolute path (gives unknown token)
	PWD should be updated - yes
	fd always 2? - fixed
	tilda support?
	// if (access(dir, F_OK) != 0)
	// 	return (ft_cd_error(data, "cd: no such file or directory: ", dir));
	// if (access(dir, X_OK) != 0)
	// 	return (ft_cd_error(data, "cd: permission denied: ", dir));
*/

static void	ft_cd_error(t_data *data, const char *msg, const char *arg)
{
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd((char *)arg, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = ERROR_GENERIC;
}

static t_env	*ft_search_list(const char *key, t_env *env)
{
	t_env	*temp;
	size_t	key_len;

	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, key_len) == 0
			&& temp->key[key_len] == '\0')
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_cd(t_command *commands, t_data *data)
{
	t_env	*home_env;
	char	*dir;

	home_env = data->env;
	if (!commands->command[1])
	{
		home_env = ft_search_list("HOME", data->env);
		if (!home_env)
			return (ft_cd_error(data, "cd: HOME not set", NULL));
		dir = home_env->value;
	}
	else if (commands->command[2])
		return (ft_cd_error(data, "cd: too many arguments: "
				, commands->command[2]));
	else
		dir = commands->command[1];
	if (chdir(dir) != 0)
		return (ft_cd_error(data, "cd: error changing directory: ", dir));
	data->exit_status = SUCCESS;
}
