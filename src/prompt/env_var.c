#include "lexer.h"
#include "parser.h"
#include "minishell.h"


t_env *create_env_node(const char *env_var)
{
	t_env	*node;
	char	*delimiter;
	size_t	name_len;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("malloc");
		return NULL;
	}

	delimiter = ft_strchr(env_var, '=');
	if (!delimiter)
	{
		free(node);
		return NULL;
	}

	name_len = delimiter - env_var;
	node->name = strndup(env_var, name_len); // implement in libft
	node->value = ft_strdup(delimiter + 1);
	node->next = NULL;

	if (!node->name || !node->value)
	{
		free(node->name);
		free(node->value);
		free(node);
		return NULL;
	}

	return node;
}

void free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

int add_env_node(t_env **env_list, t_env **last_node, const char *env_var)
{
	t_env *new_node;

	new_node = create_env_node(env_var);
	if (!new_node)
	{
		perror("Failed to create env node");
		return 1;
	}

	if (!*env_list)
		*env_list = new_node;
	else
		(*last_node)->next = new_node;
	*last_node = new_node;
	return 0;
}

int init_env(t_data *data, char **envp)
{
	t_env	*env_list;
	t_env	*last_node;
	int	i;

	env_list = NULL;
	last_node = NULL;
	i = 0;
	while (envp[i])
	{
		if (add_env_node(&env_list, &last_node, envp[i]) != 0)
		{
			free_env_list(env_list);
			return 1;
		}
		i++;
	}
	data->env = env_list;
	return 0;
}
