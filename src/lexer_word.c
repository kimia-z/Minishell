#include "lexer.h"

void lexer_collect_word(t_lexer *lexer, t_tokenlist *tokenlist)
{
	size_t	start;
	size_t	len;

	lexer_skip_whitespace(lexer);
	start = lexer->position;
	while (lexer->position < lexer->length && !is_metacharacter(lexer->input[lexer->position]))
	{
		lexer->position++;
	}
	len = lexer->position - start;
	create_word_token(start, len, lexer, tokenlist);
}

