/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 11:12:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/10/29 12:14:38 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

// TODO:
// need a function to make a copy of it for builtins probably
// implement ft_strndup in libft
// make sure in get_env(), if things failed halfway, the previous resources are properly freed
// malloc for data->envp = envp;


// NOTES
// can i use environ instead of all this? (as an extern var)

//ask from Yasaman: is list like this?
//key : USER
//value : kziari
static void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free_env_node(temp);
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
	node->key = strndup(env_var, len); // implement in libft
	node->value = ft_strdup(delimiter + 1);
	node->next = NULL;
	if (!node->key || !node->value)
		return (NULL);
	return (node);
}

static int	add_env_node(t_env **env_list, t_env **last_node, const char *env_var)
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

/* 0 for success, -1 for env null*/
int get_env(t_data *data, char **envp)
{
	t_env	*env_list;
	t_env	*last_node;
	int		i;

	env_list = NULL;
	last_node = NULL;
	i = 0;
	//data->envp = envp;
	while (envp[i])
	{
		if (add_env_node(&env_list, &last_node, envp[i]) != 0)
			return (free_env_list(env_list), -1);
		i++;
	}
	data->env = env_list;
	return (0);
}
