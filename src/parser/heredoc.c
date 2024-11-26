/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 18:52:18 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/11/26 19:14:21 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

char	*handle_heredoc(const char *delimiter)
{
    printf("wooho heredoc\n");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *heredoc_content = NULL;
    size_t heredoc_size = 0;

    printf("heredoc> ");
    while ((read = getline(&line, &len, stdin)) != -1)
    {
        if (strncmp(line, delimiter, strlen(delimiter)) == 0 && line[strlen(delimiter)] == '\n')
            break;
        heredoc_content = realloc(heredoc_content, heredoc_size + read + 1);
        if (!heredoc_content)
        {
            perror("realloc");
            free(line);
            return NULL;
        }
        memcpy(heredoc_content + heredoc_size, line, read);
        heredoc_size += read;
        heredoc_content[heredoc_size] = '\0';
        printf("heredoc> ");
    }

    free(line);
    return heredoc_content;
}