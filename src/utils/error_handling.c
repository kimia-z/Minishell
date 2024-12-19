/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 12:41:05 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 14:57:14 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

/* Writing errors to STDERR */
void	write_stderr(char *errmsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	cleanup_memory_alloc(t_data *data)
{
	if (data->envp)
	{
		/*printf("Freeing envp\n");
		print_envp(data->envp); // Debug statement*/
		free_2d((void ***)&data->envp);
	}
	if (data->env)
	{
		/*printf("Freeing env list\n");
		print_env_list(data->env);
		printf("\n\n");*/
		free_env_list(data->env);
	}
	free_history(&data->history);
}

void	end_shell(t_data *data)
{
	cleanup_memory_alloc(data);
	save_history(&data->history, HISTORY_FILE);
	free_history(&data->history);
	rl_clear_history();
	/*clear_history(); // on mac*/
	rl_free_line_state();
	rl_cleanup_after_signal();
}
