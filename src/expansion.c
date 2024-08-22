#include "lexer.h"

char	*expand_env_var(char *d_quote)
{
	char	buffer[1024] = {0};
	char	var_name[256];
	char	*delimiter_chars;
	char	*env_var;
	char	*result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	delimiter_chars = " \t\n\r";
	while ((d_quote[i]))
	{
		if (d_quote[i] == '$')
		{
			//skip $
			i++;
			//take var name
			k = 0;
			while (!ft_strchr(delimiter_chars, d_quote[i]) && d_quote[i])
			{
				var_name[k++] = d_quote[i++];
			}
			//null terminated the var name
			var_name[k] = '\0';
			//take the value of env variable
			env_var = getenv(var_name);
			if (env_var)
			{
				//add the value to buffer
				while(*env_var)
				{
					buffer[j++] = *env_var++;
				}
			}
			else
			{
				//if did not find the value copy the var name to buffer
				strcpy(&buffer[j], "$");
				j++;
				strcpy(&buffer[j], var_name);
				j += ft_strlen(var_name);
			}
		}
		//copy other characters
		else
		{
			buffer[j++] = d_quote[i++];
		}
	}
	buffer[j] = '\0';
	result = malloc (ft_strlen(buffer) + 1);
	strcpy(result, buffer);
	return (result);
}
