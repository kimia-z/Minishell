#include <lexer.h>

void	exit_program()
{
	
}

void	error_msg(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit_program();
}
