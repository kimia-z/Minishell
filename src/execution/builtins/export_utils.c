/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:14:26 by kziari            #+#    #+#             */
/*   Updated: 2024/12/12 19:14:28 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
		node->value = ft_strdup(value);
	else
		node->value = ft_strdup("");
	if (node->value == NULL)
		return (NULL);
	return (node);
}

bool	add_node(t_env *env, char *key, char *value, bool is_with_sign)
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

void	error_export(char *msg, t_data *data)
{
	write_stderr(msg);
	data->exit_status = ERROR_GENERIC;
}

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

bool	is_valid(t_data *data, char **current_cmd, int i)
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
