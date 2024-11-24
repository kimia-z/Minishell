#include "lexer.h"
#include "parser.h"
#include "minishell.h"

void print_command_list(t_command *cmdlist)
{
    t_command *current = cmdlist;
    //int i;

    while (current != NULL)
    {
        for (int j = 0; current->command[j]; j++)
        {
            printf("Command: %s\n", current->command[j]);
        }
        printf("Arguments: ");
        // if (current->args != NULL)
        // {
        //     for (i = 0; current->args[i] != NULL; i++)
        //     {
        //         printf("%s ", current->args[i]);
        //     }
        // }
        printf("\n");

        if (current->redirect_in != NULL)
            printf("Redirect In: %s\n", current->redirect_in);
        if (current->redirect_out != NULL)
            printf("Redirect Out: %s\n", current->redirect_out);
        if (current->redirect_append != NULL)
            printf("Redirect Append: %s\n", current->redirect_append);
		    if (current->path != NULL)
            printf("Path: %s\n", current->path);

        current = current->next;
        printf("\n");
    }
}

void tokenlist_print(t_token *head)
{
	int i = 0;
	t_token *current = head;
	while (current != NULL)
	{
		printf("%d  - ", i);

		printf("Token Type: %d, Token Value: %s", current->type, current->value);
		current = current->next;
		i++;
	}
}