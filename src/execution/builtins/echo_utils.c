/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/23 14:13:48 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/12/23 14:24:50 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_exit_code(char **result, char *exit_code_str, char *arg)
{
	char	*temp;
	size_t	len;

	temp = ft_strstr(*result, "$?");
	while (temp != NULL)
	{
		len = temp - *result;
		temp = ft_strjoin(ft_substr(*result, 0, len), exit_code_str);
		free(*result);
		*result = ft_strjoin(temp, arg + len + 2);
		free(temp);
		temp = ft_strstr(*result, "$?");
	}
}
