/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 15:54:56 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/12/19 16:11:39 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

static char	**path_variable(void)
{
	char	**directories;
	char	*path;

	path = getenv("PATH");
	if (path == NULL)
	{
		return (NULL);
	}
	directories = ft_split(path, ':');
	if (directories == NULL)
	{
		return (NULL);
	}
	return (directories);
}

// Function to check if a command is executable
static bool	is_command_legit(char *command)
{
	return (access(command, F_OK | X_OK) == 0);
}

// Function to construct the full path of a command
static char	*construct_command(char *commandname)
{
	size_t	len;
	char	**path_v;
	char	*command_path;
	int		i;

	i = 0;
	path_v = path_variable();
	if (!path_v)
		return (NULL);
	while (path_v[i] != NULL)
	{
		len = ft_strlen(path_v[i]) + ft_strlen(commandname) + 2;
		command_path = malloc(len * sizeof(char));
		if (!command_path)
			return (free_2d((void ***)&path_v), NULL);
		ft_strlcpy(command_path, path_v[i], len);
		ft_strlcat(command_path, "/", len);
		ft_strlcat(command_path, commandname, len);
		if (is_command_legit(command_path))
			break ;
		free(command_path);
		command_path = NULL;
		i++;
	}
	return (free_2d((void ***)&path_v), command_path);
}

/* returns command's full path */
char	*find_path(char *commandname)
{
	char	*command_path;

	if (commandname == NULL || commandname[0] == '\0')
	{
		printf("error\n");
		return (NULL);
	}
	if (commandname[0] == '/' && is_command_legit(commandname))
		return (ft_strdup(commandname));
	if (ft_strncmp(commandname, "./", 2) == 0)
		return (ft_strdup(commandname));
	command_path = construct_command(commandname);
	if (command_path == NULL)
		return (NULL);
	return (command_path);
}
