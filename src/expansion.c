#include "lexer.h"
int get_env_len(char *arg)
{
    char    *env_var;
    int     i;
    i = 0;
    // ignore the $ sign
    env_var = ft_strchr(arg, '$') + 1;
    while ((env_var[i] >= 'A' && env_var[i] <= 'Z') || (env_var[i] >= 'a' && env_var <= 'z')
        || (env_var[i] >= '0' && env_var[i] <= '9' && i != 0) || env_var[i] == '_')
    {
        i++;
    }
    if (i == 0 && (env_var[i] == '?' || env_var[i] == '$'))
    {
        i = 1;
    }
    return (i);
}
//exp: echo $USER | echo hello -> 23 -- echo kziari | echo hello -> 24
char    *expand_env_var(char *arg)
{
    int     len;
    char    *var_name;
    char    *env_var;
    char    *expand_str;
    // length of the variable
    len = get_env_len(arg);
    if (len == 0)
    {
        //could not find $
    }
    var_name = malloc(len + 1);
    if (!var_name)
    {
        // error
    }
    ft_strlcpy(var_name, ft_strchr(arg, '$') + 1, len + 1);
    // var_name = "USER\n" -> 4
    env_var = getenv(var_name);
    // env_var = "kziari" -> 6
    if (!env_var)
    {
        //could not find in env_var
    }
    expand_str = malloc(ft_strlen(env_var) + ft_strlen(arg) - (ft_strlen(var_name) + 1));
    if (!expand_str)
    {
        //failed
    }
    ft_strlcpy(expand_str, arg, ft_strchr(arg, '$') - arg + 1);
    // expand_str = echo
    ft_strlcpy(expand_str + (ft_strchr(arg, '$') - arg), env_var, ft_strlen(env_var) + 1);
    // expand_str = echo kziari
    ft_strlcpy(expand_str + (ft_strchr(arg, '$') - arg) + ft_strlen(env_var), (ft_strchr(arg, '$') + ft_strlen(var_name) + 1), ft_strlen(ft_strchr(arg, '$') + ft_strlen(var_name)) + 1);
    // expand_str = echo kziari | echo hello
    free (arg);
    return (expand_str);
}