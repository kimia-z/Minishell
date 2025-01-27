/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/12 17:17:33 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 13:10:13 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

char	*replace_variable(char *expanded, char *var_start, char *var_value)
{
	char	*before_var;
	char	*after_var;
	char	*new_expanded;
	char	*final_expanded;
	size_t	var_name_len;

	var_name_len = 0;
	while (ft_isalnum(var_start[var_name_len + 1]) || \
	var_start[var_name_len + 1] == '_')
		var_name_len++;
	before_var = ft_substr(expanded, 0, var_start - expanded);
	after_var = ft_strdup(var_start + var_name_len + 1);
	new_expanded = ft_strjoin(before_var, var_value);
	final_expanded = ft_strjoin(new_expanded, after_var);
	free(before_var);
	free(after_var);
	free(new_expanded);
	free(expanded);
	return (final_expanded);
}

char	*skip_single_quotes(char *expanded, char *var_start)
{
	char	*single_quote_start;
	char	*single_quote_end;

	single_quote_start = ft_strchr(expanded, '\'');
	if (single_quote_start && single_quote_start < var_start)
	{
		single_quote_end = ft_strchr(single_quote_start + 1, '\'');
		if (single_quote_end && single_quote_end > var_start)
		{
			var_start = ft_strchr(single_quote_end + 1, '$');
		}
	}
	return (var_start);
}

static char	*process_variable(char *expanded, char *var_start, char **envp)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(var_start);
	var_value = get_env_value(var_name, envp);
	free(var_name);
	if (var_value)
	{
		expanded = replace_variable(expanded, var_start, var_value);
		free(var_value);
	}
	return (expanded);
}

char	*expand_variables(const char *input, char **envp)
{
	char	*expanded;
	char	*var_start;

	expanded = ft_strdup(input);
	var_start = ft_strchr(expanded, '$');
	while (var_start)
	{
		var_start = skip_single_quotes(expanded, var_start);
		if (!var_start)
			break ;
		if (!ft_isalnum(*(var_start + 1)) && *(var_start + 1) != '_')
		{
			var_start = ft_strchr(var_start + 1, '$');
			continue ;
		}
		expanded = process_variable(expanded, var_start, envp);
		var_start = ft_strchr(expanded, '$');
	}
	return (expanded);
}
