/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 17:17:33 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/05 21:58:24 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

char	*get_env_value(const char *var_name, char **envp)
{
	size_t len;
	int		i;

	i = 0;
	len = ft_strlen(var_name);
	while(envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
		
	}
	return (ft_strdup(""));
}

char	*get_var_name(const char *var_start)
{
	const char	*var_end;

	var_end = var_start + 1;
	while (ft_isalnum(*var_end) || *var_end == '_')
		var_end++;
	return (ft_substr(var_start + 1, 0, var_end - var_start - 1));
}

char	*replace_variable(char *expanded, char *var_start, char *var_value)
{
	char	*before_var;
	char	*after_var;
	char	*new_expanded;
	char	*final_expanded;

	before_var = ft_substr(expanded, 0, var_start - expanded);
	after_var = ft_strdup(var_start + strlen(var_value) + 1);
	new_expanded = ft_strjoin(before_var, var_value);
	final_expanded = ft_strjoin(new_expanded, after_var);
	free(before_var);
	free(after_var);
	free(new_expanded);
	free(expanded);
	return (final_expanded);
}

char	*expand_variables(const char *input, char **envp)
{
	char	*expanded;
	char	*var_start;
	char	*var_name;
	char	*var_value;

	expanded = ft_strdup(input);
	var_start = ft_strchr(expanded, '$');
	while (var_start)
	{
		var_name = get_var_name(var_start);
		var_value = get_env_value(var_name, envp);
		free(var_name);
		if (var_value)
		{
			expanded = replace_variable(expanded, var_start, var_value);
			free(var_value);
		}
		var_start = ft_strchr(expanded, '$');
	}
	return (expanded);
}
