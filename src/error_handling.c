#include "lexer.h"


/* Writing errors to STDERR */
void	write_stderr(char *errmsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (errmsg)
		ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// void	cleanup(t_tokenlist *tokenlist)
// {
// 	tokenlist_free(tokenlist);

// }