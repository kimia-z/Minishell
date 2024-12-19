/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 16:36:12 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 12:57:19 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

int	g_exit_code;

void	parent_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = ERROR_CTRL_C_;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(ERROR_CTRL_C_);
	}
}

int	signal_mode(int mode)
{
	if (mode == MINISHELL)
	{
		if (signal(SIGINT, parent_sig_handler) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (-1);
	}
	else if (mode == CHILD)
	{
		if (signal(SIGINT, parent_sig_handler) == SIG_ERR || \
		signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			return (-1);
	}
	else if (mode == HERE_DOC)
	{
		if (signal(SIGINT, heredoc_sig_handler) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (-1);
	}
	else if (mode == IGNORE)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (-1);
	}
	return (0);
}
