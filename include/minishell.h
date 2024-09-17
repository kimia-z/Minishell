/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:58:32 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/09/17 15:30:55 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


#include "lexer.h"
#include "parser.h"

typedef struct s_data
{
	char	**envp;

}               t_data;

int bridge_function(void);


#endif

