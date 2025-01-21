/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/21 23:13:44 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

# define PATH_MAX 1024
# define MAX_STATUS_LEN 20
# define EXIT_ERROR_CODE 255

typedef struct s_exec
{
	char			**argv;
	char			***env_ptr; //a ptr to the env var array, can directly update
	int				*exitcode;
	struct s_cmd	*next;
	t_token_type	type;
}	t_exec;

#endif
