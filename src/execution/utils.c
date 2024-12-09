#include "execution.h"


// char	*ft_strtrim_beginning(char const *s1, char const *set)
// {
// 	char	*new_s1;
// 	int		start;
// 	int		end;
// 	int		new_len;

// 	start = 0;
// 	end = ft_strlen(s1) -1;
// 	while ((s1[start] != '\0' && s1[start] == set[start])
// 		|| s1[start] == ' ')
// 		start++;
// 	start++;
// 	new_len = end - start + 2;
// 	new_s1 = (char *)malloc(sizeof(char) * new_len);
// 	if (new_s1 == NULL)
// 		return (NULL);
// 	ft_strlcpy(new_s1, s1 + start, new_len);
// 	return (new_s1);
// }

// static t_env	*new_env(char *env)
// {
// 	t_env	*env_list;
// 	char	*temp;
// 	int		i;

// 	env_list = malloc(sizeof(t_env));
// 	if (env_list == NULL)
// 		return (ft_putstr_fd("Erro to create env node\n", 2), NULL);
// 	i = 0;
// 	while (env[i] != '=')
// 		i++;
// 	env_list->key = ft_calloc(sizeof(char), i + 1);
// 	if (env_list->key == NULL)
// 		return (free(env_list), NULL);
// 	ft_strlcpy(env_list->key, env, (i + 1));
// 	temp = ft_strtrim_beginning(env, env_list->key);
// 	env_list->value = ft_strdup(temp);
// 	free(temp);
// 	env_list->next = NULL;
// 	return (env_list);
// }

// static void	add_env_back(t_env **head, void *content)
// {
// 	t_env	*current_node;
// 	t_env	*new_node;

// 	current_node = *head;
// 	while (current_node->next != NULL)
// 	{
// 		current_node = current_node->next;
// 	}
// 	new_node = new_env(content);
// 	current_node->next = new_node;
// }

// t_env	*initial_env(char **env)
// {
// 	t_env	*env_list;
// 	int		i;

// 	env_list = new_env(env[0]);
// 	if (env_list == NULL)
// 		return (NULL);
// 	i = 1;
// 	while (env[i] != NULL)
// 	{
// 		add_env_back(&env_list, env[i]);
// 		i++;
// 	}
// 	return (env_list);
// }
// char	*ft_strcat(char *dest, const char *src)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (dest[i] != '\0')
// 		i++;
// 	j = 0;
// 	while (src[j] != '\0')
// 	{
// 		dest[i + j] = src[j];
// 		j++;
// 	}
// 	dest[i + j] = '\0';
// 	return (dest);
// }

void	free_env_list_2(t_env *head)
{
	t_env	*temp;
	t_env	*change;

	temp = head;
	if (head == NULL)
		return ;
	while (temp != NULL)
	{
		free(temp->key);
		free(temp->value);
		change = temp->next;
		free(temp);
		temp = change;
	}
}

int	ft_strchr_pos(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	return (0);
}

void	free_2arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int my_lstsize(t_env *lst)
{
	int count;

	count = 0;
	if (lst == NULL)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_env *my_lstnew(char *key, char *value)
{
	t_env *new_node;

	new_node = (t_env *)malloc(1 * sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env *my_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void my_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = my_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
