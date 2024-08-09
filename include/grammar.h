#ifndef GRAMMAR_H
# define GRAMMAR_H

#include "lexer.h"


/************************************************************/
/*  Structs */


typedef struct	s_filename
{
	char	*word;
}			t_filename;

typedef struct	s_io_redirect
{
	t_io_file	*io_file;
	t_io_here	*io_here;
}			t_io_redirect;

// Not sure if the redirect should be char or char*
typedef struct	s_io_file
{
	char		*i_redirect;
	char		*o_redirect;
	char		*append_redirect;
	t_filename	*filename;
}			t_io_file;

typedef struct	s_io_here
{
	char		*here_doc;
	t_here_end	*here_end;
}			t_io_here;

typedef struct	s_here_end
{
	char	*word;
}			t_here_end;

typedef struct s_simple_command
{
	t_cmd_prefix	*prefix;
	t_cmd_suffix	*suffix;
	t_cmd_word		*word;
	t_cmd_name		*name;
}			t_simple_command;

typedef struct	s_cmd_name
{
	char	*word;
}			t_cmd_name;

typedef struct	s_cmd_word
{
	char	*word;
}			t_cmd_word;

typedef struct s_cmd_prefix
{
	t_io_redirect	*io_redirect;
	t_cmd_prefix	*prefix;
}			t_cmd_prefix;

typedef struct s_cmd_suffix
{
	t_io_redirect	*io_redirect;
	t_cmd_suffix	*suffix;
	char			*word;
}			t_cmd_suffix;

typedef struct	s_pipe_seq
{
	t_simple_command	*simple_cmd;
	char				*pipe;
}			t_pipe_seq;


#endif


