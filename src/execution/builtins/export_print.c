/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:01:35 by kziari            #+#    #+#             */
/*   Updated: 2024/12/12 21:01:36 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_env	*ft_copy_list(t_env *env_vars)
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

static void	sort_helper(t_env *temp_list)
{
	char	*temp;

	temp = temp_list->key;
	temp_list->key = temp_list->next->key;
	temp_list->next->key = temp;
	temp = temp_list->value;
	temp_list->value = temp_list->next->value;
	temp_list->next->value = temp;
}

static t_env	*ft_sort_env(t_env *env_vars)
{
	t_env	*temp_list;
	t_env	*copy_list;
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
				sort_helper(temp_list);
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
