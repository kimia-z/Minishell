#include <lexer.h>

void	lexer_collect_squote(t_lexer *lexer, t_tokenlist *tokenlist, size_t len)
{
	create_word_token(lexer->position, len, lexer, tokenlist);
	lexer->position += len + 1;
}

void	lexer_collect_dquote(t_lexer *lexer, t_tokenlist *tokenlist, size_t len)
{
	create_word_token(lexer->position, len, lexer, tokenlist);
	lexer->position += len + 1;

}

void	lexer_collect_quotes(t_lexer *lexer, char *value, t_tokenlist *tokenlist)
{
	size_t len;

	if (!is_quote_closed(lexer, value))
	{
		//error unclosed
		return ;
	}
	len = len_quotes(value);
	lexer->position++;
	if (*value == '\'')
		lexer_collect_squote(lexer, tokenlist, len);
	else if (*value == '"')
		lexer_collect_dquote(lexer, tokenlist, len);
}

