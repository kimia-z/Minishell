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

void	f_env_list(t_env **env_list)
{
	t_env	*current;
	t_env	*next;

	if (!env_list || !*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*env_list = NULL;
}

static t_env	*create_new_env_node(char *key, char *value, bool is_with_sign)
{
	t_env	*node;

	node = malloc(1 * sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->key = ft_strdup(key);
	if (node->key == NULL)
		return (NULL);
	if (is_with_sign == false)
	{
		node->value = NULL;
		return (node);
	}
	if (value != NULL)
	{
		node->value = ft_strdup(value);
		if (node->value == NULL)
			return (NULL);
	}
	else
	{
		node->value = ft_strdup("");
		if (node->value == NULL)
			return (NULL);
	}
	return (node);
}

bool	add_node_env(t_env *env, char *key, char *value, bool is_with_sign)
{
	t_env	*temp;
	t_env	*new_node;

	temp = env;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	new_node = create_new_env_node(key, value, is_with_sign);
	if (new_node == NULL)
		return (false);
	temp->next = new_node;
	return (true);
}
/*
	return value: found=1
	return value: not_found=0
	return value: failed=-1
*/

int	search_node_env(t_env *env, char *key, char *value, bool is_with_sign)
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
				if (temp->value == NULL)
					return (-1);
			}
			else if (value == NULL && is_with_sign == true)
			{
				free(temp->value);
				temp->value = ft_strdup("");
				if (temp->value == NULL)
					return (-1);
			}
			else if (value == NULL && is_with_sign == false)
				return (1);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

bool	key_with_value(t_data *data, t_env *env, char *cmd)
{
	char	*key;
	char	*value;
	int		position;
	char	*temp;
	int		is_found;

	temp = cmd;
	position = ft_strchr_pos(cmd, '=');
	value = ft_strchr(temp, '=') + 1;
	key = malloc((position + 1) * sizeof(char));
	if (key == NULL)
		return (false);
	ft_strlcpy(key, cmd, position + 1);
	is_found = search_node_env(env, key, value, true);
	if (is_found == -1)
		return (false);
	if (is_found == 0)
	{
		if (add_node_env(env, key, value, true) == false)
		{
			if (key != NULL)
				free(key);
			return (false);
		}
	}
	if (key != NULL)
		free(key);
	return (true);
}

static bool	is_valid(t_data *data, char **current_cmd, int i)
{
	if (ft_isalpha(current_cmd[i][0]) == 0)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(current_cmd[i], STDERR_FILENO);
		ft_putendl_fd(" : not a valid identifier", STDERR_FILENO);
		data->exit_status = ERROR_GENERIC;
		return (false);
	}
	return (true);
}

t_env	*ft_copy_list(t_env *env_vars)
{
	t_env	*copy_list;
	t_env	*new_node;
	int		len;

	copy_list = NULL;
	len = my_lstsize(env_vars);
	while (len > 0)
	{
		new_node = my_lstnew(env_vars->key, env_vars->value);
		if (new_node == NULL)
		{
			f_env_list(&copy_list);
			return (NULL);
		}
		my_lstadd_back(&copy_list, new_node);
		env_vars = env_vars->next;
		len--;
	}
	return (copy_list);
}

t_env	*ft_sort_env(t_env *env_vars)
{
	t_env	*temp_list;
	t_env	*copy_list;
	char	*temp;
	int		len_list;

	temp_list = env_vars;
	copy_list = ft_copy_list(temp_list);
	if (copy_list == NULL)
		return (NULL);
	len_list = my_lstsize(copy_list);
	while (len_list > 0)
	{
		temp_list = copy_list;
		while (temp_list && temp_list->next)
		{
			if (strcmp(temp_list->key, temp_list->next->key) > 0)
			{
				temp = temp_list->key;
				temp_list->key = temp_list->next->key;
				temp_list->next->key = temp;
				temp = temp_list->value;
				temp_list->value = temp_list->next->value;
				temp_list->next->value = temp;
			}
			temp_list = temp_list->next;
		}
		len_list--;
	}
	return (copy_list);
}

bool	print_export(t_data *data, int outfile)
{
	t_env	*sorted_env;
	t_env	*temp;

	temp = data->env;
	sorted_env = ft_sort_env(temp);
	if (sorted_env == NULL)
		return (false);
	temp = sorted_env;
	while (temp)
	{
		ft_putstr_fd("declare -x ", outfile);
		ft_putstr_fd(temp->key, outfile);
		if (temp->value == NULL)
			ft_putchar_fd('\n', outfile);
		else if (temp->value)
		{
			ft_putstr_fd("=\"", outfile);
			ft_putstr_fd(temp->value, outfile);
			ft_putstr_fd("\"", outfile);
			ft_putchar_fd('\n', outfile);
		}
		temp = temp->next;
	}
	f_env_list(&sorted_env);
	return (true);
}

void	error_export(char *msg, t_data *data)
{
	write_stderr(msg);
	data->exit_status = ERROR_GENERIC;
}

//Handles the export of environment variables in the shell.
//either display all environment variables in the current shell (sorted env)
//or to add/update environment variables based on the provided

void	ft_export(t_command *commands, t_data *data)
{
	int	outfile;
	int	i;
	int	is_found;

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
	while (commands->command[++i])
	{
		if (is_valid(data, commands->command, i) == true)
		{
			if (ft_strchr(commands->command[i], '=') != NULL)
			{
				if (key_with_value(data, data->env, commands->command[i]) == false)
					return (error_export("failed in memory allocate", data));
			}
			else
			{
				is_found = search_node_env(data->env, commands->command[i], NULL, false);
				if (is_found == 0)
				{
					if (add_node_env((data->env), commands->command[i], NULL, false) == false)
						return (error_export("failed in memory allocate", data));
				}
				else if (is_found == -1)
					return (error_export("failed in memory allocate", data));
			}
		}
	}
	data->exit_status = SUCCESS;
}
