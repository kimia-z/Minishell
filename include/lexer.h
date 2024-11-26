/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/19 21:07:57 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/11/26 19:24:05 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/wait.h>

/* **************************************************************************** */ 
/* Structs */

enum e_token_type
{
	TOKEN_WORD,
	TOKEN_OP_REDIRECTION_OUT, // >
	TOKEN_OP_REDIRECTION_IN, // <
	TOKEN_OP_REDIRECTION_APPEND, // >> 
	TOKEN_OP_PIPE,
	TOKEN_OP_HEREDOC, // <<
	TOKEN_UNKNOWN
};


typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	size_t				size;
	struct s_token		*next;
}				t_token;

// an array of tokens
typedef struct s_tokenlist
{
	size_t				token_count;
	t_token				*head;
}				t_tokenlist;

/* members of this struct need to be updated later on */
typedef struct s_lexer
{
	t_token				**tokens;
	unsigned int		position;
	char				*input;
	size_t				length;
	char				start;
}						t_lexer;

/* **************************************************************************** */ 

/* Lexer functions */
t_lexer				*lexer_init(char *input);
enum e_token_type	get_operator_type(char *value);
void				lexer_free(t_lexer *lexer);
void				*lexer_collect_token(t_lexer *lexer, t_tokenlist *tokenlist, bool is_op);
int					lexer_main(t_lexer *lexer, t_tokenlist *tokenlist);
void				*lexer_collect_quotes(t_lexer *lexer, char *value, t_tokenlist *tokenlist, bool is_op);
void				lexer_skip_whitespace(t_lexer *lexer);


/* Token functions */
t_token		*token_create(enum e_token_type type, char *value);
void		token_free(t_token *token);

/* Tokenlist functions */
t_tokenlist	*tokenlist_init(void);
void		tokenlist_free(t_tokenlist *list);
void		tokenlist_add(t_tokenlist *list, t_token *token);
void		tokenlist_print(t_token *head);


#endif


