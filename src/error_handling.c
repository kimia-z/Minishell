#include "lexer.h"
#include "parser.h"

/* Writing errors to STDERR */
void	write_stderr(char *errmsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (errmsg)
		ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void free_command(t_command *command)
{
    int i;

    if (command == NULL)
        return;

    if (command->command != NULL)
        free(command->command);

    if (command->args != NULL)
    {
        for (i = 0; command->args[i] != NULL; i++)
        {
            free(command->args[i]);
        }
        free(command->args);
    }
    if (command->redirect_in != NULL)
        free(command->redirect_in);
    if (command->redirect_out != NULL)
        free(command->redirect_out);
    if (command->redirect_append != NULL)
        free(command->redirect_append);

    free(command);
}

void free_command_list(t_command *cmdlist)
{
    t_command *current = cmdlist;
    t_command *next;

    while (current != NULL)
    {
        next = current->next;
        free_command(current);
        current = next;
    }
}