/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/21 17:59:20 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECTOR_H
#define EXECTOR_H

# include "minishell.h"

# define PATH_MAX 1024

typedef struct s_cmd
{
	char			**argv;
	char			***env_ptr;
	int				*exitcode;
	struct s_cmd	*next;
	t_token_type	type;
}	t_cmd;
