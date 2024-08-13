#include <lexer.h>

/* get the env variable and return it*/
char	*get_env_var(char *point_to_dollar_sign)
{
	size_t	len_org_env_var;
	char	*org_env_var;
	char	*processed_env_var;

	len_org_env_var = 1;
	//maybe here add if $$
	while (!ft_isspace(point_to_dollar_sign[len_org_env_var]) && point_to_dollar_sign[len_org_env_var] != '"')
	{
		len_org_env_var++;
	}
	org_env_var = strndup(point_to_dollar_sign + 1, len_org_env_var - 1);
	processed_env_var = getenv(org_env_var);
	free (org_env_var);
	if (!processed_env_var)
	{
		// if it could not find it it should ignore whole $vriable
	}
	return (processed_env_var);
}

char	*ft_expantion(char *d_quote, size_t len)
{
	size_t	i;
	char	*point_to_dollar_sign;
	char	*processed_env_var;
	char	*processed_d_quote;

	i = 0;
	while (i < len)
	{
		point_to_dollar_sign = d_quote + i;
		if (point_to_dollar_sign[0] == '$' && !ft_isspace(*point_to_dollar_sign + 1))
		{
			ft_realloc(d_quote, i + 1);
			processed_env_var = get_env_var(point_to_dollar_sign);
		}
		i++;
	}
}
//"salam $env_var bye!"
// len = 19;
// len env = 8; with dollar sign
// void	lexer_collect_dquote(t_lexer *lexer, t_tokenlist *tokenlist, size_t len)
// {
// 	size_t	start;
// 	size_t	i;
// 	char	*point_to_dollar_sign;
// 	char	*processed_env_var;

// 	start = lexer->position;
// 	i = 0;
// 	lexer->quote = strndup(lexer->input + start, len);
// 	if (!lexer->quote)
// 	{
// 		//error
// 		return ;
// 	}
// 	lexer->is_quote = true;
// 	while (i < len)
// 	{
// 		point_to_dollar_sign = lexer->quote + i;
// 		if (point_to_dollar_sign[0] == '$' && !ft_isspace(*point_to_dollar_sign + 1))
// 		{
// 			processed_env_var = lexer_get_env_var(point_to_dollar_sign);
// 			printf("processed_env_var=%s\n", processed_env_var);
// 		}
// 		i++;
// 	}
// 	create_word_token(start, len, lexer, tokenlist);
// 	lexer->position += len + 1;
// 	printf("where is position after duoble=%s\n", lexer->input + lexer->position);

// }