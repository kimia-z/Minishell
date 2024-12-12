/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:18:32 by kziari            #+#    #+#             */
/*   Updated: 2024/12/09 13:18:33 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
	return value: found=1
	return value: not_found=0
	return value: failed=-1
*/

static int	search_node(t_env *env, char *key, char *value, bool is_with_sign)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, sizeof(key)) == 0)
		{
			if (value != NULL)
			{
				free(temp->value);
				temp->value = ft_strdup(value);
			}
			else if (value == NULL && is_with_sign == true)
			{
				free(temp->value);
				temp->value = ft_strdup("");
			}
			if (temp->value == NULL)
				return (-1);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static bool	k_with_v(t_data *data, t_env *env, char *cmd, char *temp)
{
	char	*key;
	char	*value;
	int		position;
	int		is_found;
	bool	return_value;

	return_value = true;
	position = ft_strchr_pos(cmd, '=');
	value = ft_strchr(temp, '=') + 1;
	key = malloc((position + 1) * sizeof(char));
	if (key == NULL)
		return (false);
	ft_strlcpy(key, cmd, position + 1);
	is_found = search_node(env, key, value, true);
	if (is_found == -1)
		return_value = false;
	else if (is_found == 0 && add_node(env, key, value, true) == false)
		return_value = false;
	if (key != NULL)
		free(key);
	return (return_value);
}

static int	export_helper(t_data *data, t_command *cmds, int *i)
{
	int		is_found;
	char	*temp;

	if (ft_strchr(cmds->command[*i], '=') != NULL)
	{
		temp = cmds->command[*i];
		if (k_with_v(data, data->env, cmds->command[*i], temp) == false)
			return (-1);
	}
	else
	{
		is_found = search_node(data->env, cmds->command[*i], NULL, false);
		if (is_found == 0)
		{
			if (add_node((data->env), cmds->command[*i], NULL, false) == false)
				return (-1);
		}
		else if (is_found == -1)
			return (-1);
	}
	return (0);
}

static void	export_with_arg(t_command *cmds, t_data *data, int i)
{
	while (cmds->command[++i])
	{
		if (is_valid(data, cmds->command, i) == true)
		{
			if (export_helper(data, cmds, &i) == -1)
				return (error_export("failed in memory", data));
		}
	}
	data->exit_status = SUCCESS;
}

//Handles the export of environment variables in the shell.
//either display all environment variables in the current shell (sorted env)
//or to add/update environment variables based on the provided

void	ft_export(t_command *commands, t_data *data)
{
	int	outfile;
	int	i;

	i = 0;
	outfile = commands->outfile_fd;
	if (outfile == -1)
		return (error_export("export: invalid file descriptor", data));
	if (outfile == -2)
		outfile = STDOUT_FILENO;
	if (commands->command[1] == NULL)
	{
		if (print_export(data, outfile) == false)
			return (error_export("failed in memory allocate", data));
		data->exit_status = SUCCESS;
		return ;
	}
	return (export_with_arg(commands, data, i));
}
