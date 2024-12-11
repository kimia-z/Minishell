/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execution.h                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: kziari <marvin@42.fr>                         +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/12/11 13:22:48 by kziari         #+#    #+#                */
/*   Updated: 2024/12/11 13:22:50 by kziari         ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

typedef struct s_exe
{
	int	fd[2];
	int	read;
	int	i;
	int	pid;
	int	status;
}	t_exe;

typedef enum e_builtin
{
	ECH,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
	EXIT,
	UNKNOWN
}	t_builtin;

/* Builtins */
void	ft_echo(t_command *commands, t_data *data);
void	ft_pwd(t_command *commands, t_data *data);
void	ft_exit(t_command *commands, t_data *data, int nb_pipes);
void	ft_env(t_command *commands, t_data *data);
void	ft_unset(t_command *commands, t_data *data, int nb_pipes);
void	ft_cd(t_command *commands, t_data *data);
void	ft_export(t_command *commands, t_data *data);

/* Utils */
int		ft_strchr_pos(const char *s, int c);
int		my_lstsize(t_env *lst);
t_env	*my_lstnew(char *key, char *value);
t_env	*my_lstlast(t_env *lst);
void	my_lstadd_back(t_env **lst, t_env *new);

/* Pipe functions */
int		pipe_count(t_cmdlist *commands);
int		last_pipe(t_command *temp, t_exe *exec);
int		middle_pipe(t_command *temp, t_exe *exec);
int		first_pipe(t_command *temp, int *fds);
int		pipeline(t_data *data, int nb_pipes);

/* Execution */
int		ft_execute(t_data *data);
int		execute_one_cmd(t_data *data, t_command *commands);
void	ft_parent(t_command *temp, t_exe *exec);
void	ft_child(t_data *data, t_command *temp, t_exe *exec, int nb_pipes);
int		ft_dup(t_command *temp, t_exe *exec, int i, int nb_pipes);
bool	check_builtin(t_command *commands, t_data *data, int nb_pipes);

#endif
