/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/22 21:54:51 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include "env.h"

# define PATH_MAX 260
# define MAX_STATUS_LEN 20
# define EXIT_ERROR_CODE 255

typedef struct s_exec
{
	char			**argv;
	t_env			**env;
	int				argc;
	t_token_type	type;
}	t_exec;


/*builtin*/
int	execute_builtin(t_exec *cmd);
int	builtin_export(t_exec *cmd);
int	builtin_exit(t_exec *cmd);
int	builtin_cd(t_exec *cmd);

/*error*/
int error_msg(const char *msg, int include_errno);
int error_msg_format(const char *prefix, const char *arg, const char *suffix);

/*execute_tree*/
int	run_ctrl(t_tree *tree);
int	run_block(t_tree *tree);
int	run_pipe(t_tree *tree);
int	run_redir(t_tree *tree);
int	exec_cmd(t_tree *tree);

/*executor*/
void	executor(t_tree *tree);

/*utils*/
int get_exit_status(void);

#endif
