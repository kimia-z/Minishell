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

/* **************************************************************************** */ 
/* Structs */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_WHITESPACE,
	TOKEN_OP_REDIRECTION_OUT, // >
	TOKEN_OP_REDIRECTION_IN, // <
	TOKEN_OP_REDIRECTION_APPEND, // >> 
	TOKEN_OP_PIPE,
	TOKEN_UNKNOWN
}				token_type;


// a token node has type and value of char *
typedef struct s_token
{
	token_type		type;
	char			*value;
	size_t			size;
	struct s_token	*next;
}				t_token;

// an array of tokens as nodes(linked lists)
typedef struct s_tokenlist
{
	size_t			token_count;
	t_token			*head;
}				t_tokenlist;

/* members of this struct need to be updated later on */
typedef struct s_lexer
{
	t_token			**tokens; // an array of tokens
	unsigned int	position;
	char			*input; // contents of commandline
	size_t			length;
	char			start;

}			t_lexer;


/* **************************************************************************** */ 

/* Lexer functions */
void		lexer_process_input(t_lexer *lexer, t_tokenlist *tokenlist);
t_lexer		*lexer_init(char *input);
void		lexer_collect_operators(t_lexer *lexer, char *value, t_tokenlist *tokenlist);
void		lexer_collect_word(t_lexer *lexer, t_tokenlist *tokenlist);
token_type	get_operator_type(char *value);
void		lexer_free(t_lexer *lexer);
void		create_word_token(size_t start, size_t len, t_lexer *lexer, t_tokenlist *tokenlist);

/* Quotes */
void		lexer_collect_quotes(t_lexer *lexer, char *value, t_tokenlist *tokenlist);


/* Utils */
bool		is_quotes(char c);
bool		is_quote_closed(t_lexer *lexer, char *value);
size_t		len_quotes(char *value);
bool		is_metacharacter(char c);
void		lexer_skip_whitespace(t_lexer *lexer);


/* Token functions */
t_token		*token_create(token_type type, char *value);
void		token_free(t_token *token);

/* Tokenlist functions */
t_tokenlist	*tokenlist_init(void);
void		tokenlist_free(t_tokenlist *list);
void		tokenlist_add(t_tokenlist *list, t_token *token);
void		print_token_list(t_token *head);

/* Syntax check */
int syntax_checker(t_tokenlist *tokenlist);
int operator_checker(token_type type, size_t position, size_t token_count, token_type left_op);


#endif


