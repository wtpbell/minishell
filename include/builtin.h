/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/21 10:23:07 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# ifndef BUILTIN_H
#define BUILTIN_H

# include "minishell.h"

# define PATH_MAX 1024

typedef struct s_cmd
{
	char			**argv;
	char			***env_ptr;
	int				*exitcode;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_token			*env_list;
	t_token			*token_list;
	t_cmd			*cmd;
}	t_minishell;

#endif
