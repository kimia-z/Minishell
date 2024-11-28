
#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"


typedef struct s_exe
{
	int	fd[2];
	int	read;
	int	i;
	int pid;
	int	status;
}	t_exe;


// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;


// typedef struct s_command
// {
// 	char				**command;
// 	char				*path; //char **path;
// 	int					infile_fd;
// 	int					outfile_fd;
// 	char				*infile;
// 	char				*outfile;
// 	struct s_command	*next;
// }				t_command;

// typedef struct s_parser
// {
// 	int					exit_status;
// 	int					nb_pipes;
// 	struct s_command	*commands;
// 	char				**arg_env;
// 	struct s_env		*envs;
// }				t_parser;

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

int		ft_execute(t_data *data);

void	ft_echo(t_command *commands, t_data *data);
int		ft_pwd(t_command *commands, t_data *data);
void	ft_exit(t_command *commands, t_data *data, int nb_pipes);
void	ft_env(t_command *commands, t_data *data);
void	ft_unset(t_command *commands, t_data *data, int nb_pipes);
int		ft_cd(t_command *commands, t_data *data);
//void	ft_export(t_command *commands, t_data *data);


// void	ft_putendl_fd(char *s, int fd);
// void	ft_putstr_fd(char *s, int fd);
// void	ft_putchar_fd(char c, int fd);
// size_t	ft_strlen(const char *s);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// int		ft_isdigit(int c);
// int		ft_isspace(int c);
// int		ft_islower(int c);
// int		ft_isupper(int c);
// int		ft_isalpha(int c);
// void	ft_bzero(void *s, size_t n);
// char	*ft_strchr(const char *s, int c);
// void	*ft_calloc(size_t nmemb, size_t size);
// char	*ft_strdup(const char *s);
char	*ft_strtrim_beginning(char const *s1, char const *set);
//size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// char	**ft_split(char const *s, char c);
// char	*ft_strjoin(const char *s1, const char *s2);
t_env	*initial_env(char **env);
void	free_env_list_2(t_env *head);
void	write_stderr(char *errmsg);
int		ft_strchr_pos(const char *s, int c);
char	*ft_strcharjoin(char *s1, char s2);
void	free_2arr(char **array);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcharcat(char *dest, const char src);

/* Pipe functions */
int	pipe_count(t_cmdlist *commands);
int	last_pipe(t_command *temp, t_exe *exec);
int	middle_pipe(t_command *temp, t_exe *exec);
int	first_pipe(t_command *temp, int *fds);
int	pipeline(t_data *data, int nb_pipes);


int	ft_execute(t_data *data);
int	execute_one_cmd(t_data *data, t_command *commands);
void	ft_parent(t_command *temp, t_exe *exec);
void	ft_child(t_data *data, t_command *temp, t_exe *exec, int nb_pipes);
int	ft_dup(t_command *temp, t_exe *exec, int i, int nb_pipes);
bool	check_builtin(t_command *commands, t_data *data, int nb_pipes);


// void	test_echo(void);
// void	test_pwd(void);
// void	test_exit(void);
// void	test_env(char **envp);
// void	test_print_env(t_env *env);
// void	test_unset(char **envp);
// void	test_cd(char **envp);
// void	test_export(char **envp);
// void	test_one(char **envp);
// void	test_one_pipe(char **envp);
// void	test_two_pipe(char **envp);


#endif