/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:12:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 14:50:47 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

static t_env	*create_env_node(const char *env_var)
{
	t_env	*node;
	char	*delimiter;
	size_t	len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	delimiter = ft_strchr(env_var, '=');
	if (!delimiter)
		return (free(node), NULL);
	len = delimiter - env_var;
	node->key = ft_strndup(env_var, len);
	if (!node->key)
		return (free(node), NULL);
	node->value = ft_strdup(delimiter + 1);
	if (!node->value)
	{
		free(node->key);
		return (free(node), NULL);
	}
	node->next = NULL;
	return (node);
}

/*
-l on failure: if node creation failed
0 on success
*/
static int	add_env_node(t_env **env_list, t_env **last_node, \
const char *env_var)
{
	t_env	*new_node;

	new_node = create_env_node(env_var);
	if (!new_node)
		return (-1);
	if (!*env_list)
		*env_list = new_node;
	else
		(*last_node)->next = new_node;
	*last_node = new_node;
	return (0);
}

/*
-1 on failure: malloc failure - ft_strdup failure
*/
int	add_env_to_data(t_data *data, char **envp)
{
	int	env_count;
	int	i;

	i = 0;
	env_count = 0;
	while (envp[env_count])
		env_count++;
	data->envp = malloc((env_count + 1) * sizeof(char *));
	if (!data->envp)
		return (-1);
	while (i < env_count)
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
		{
			while (i > 0)
				free(data->envp[--i]);
			free(data->envp);
			return (-1);
		}
		i++;
	}
	data->envp[env_count] = NULL;
	return (0);
}

int	get_env(t_data *data, char **envp)
{
	t_env	*env_list;
	t_env	*last_node;
	int		i;

	env_list = NULL;
	last_node = NULL;
	i = 0;
	if (!envp || add_env_to_data(data, envp) == -1)
		return (-1);
	while (envp[i])
	{
		if (add_env_node(&env_list, &last_node, envp[i]) == -1)
		{
			free_2d((void ***)&data->envp);
			return (-1);
		}
		i++;
	}
	data->env = env_list;
	return (0);
}
