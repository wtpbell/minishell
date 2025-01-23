/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 17:13:26 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include <sys/types.h> 

# define PATH_MAX 260
# define MAX_STATUS_LEN 20
# define EXIT_ERROR_CODE 255

typedef struct s_process
{
	pid_t	pid;
	int		status;
}	t_process;

typedef struct s_pipeline
{
	t_process	*processes;
	int			num_processes;
}	t_pipeline;


/*builtin*/
int		execute_builtin(t_ast_node *node, t_env **env);
int		builtin_export(t_ast_node *node, t_env **env);
int		builtin_exit(t_ast_node *node);
int		builtin_cd(t_ast_node *node, t_env **env);

/*error*/
int error_msg(const char *msg, int include_errno);
int error_msg_format(const char *prefix, const char *arg, const char *suffix);

/*execute_tree*/
void	executor(t_ast_node *node);
int		exec_cmd(t_ast_node *node);
int		exec_pipe(t_ast_node *node);
int		exec_ctrl(t_ast_node *node);
int		exec_block(t_ast_node *node);
int		exec_redir(t_ast_node *node);

/*executor*/
void	executor(t_tree *tree);

/*utils*/
int get_exit_status(void);

#endif
