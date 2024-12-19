/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/19 14:31:38 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/19 14:34:03 by ykarimi       ########   odam.nl         */
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

