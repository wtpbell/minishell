/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/29 20:19:08 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include <sys/types.h> 

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


/*error*/
void error(const char *word, const char *msg);

/*execute_tree*/
void	executor(t_ast_node *node);
int		exec_cmd(t_ast_node *node);
int		exec_pipe(t_ast_node *node);
int		exec_ctrl(t_ast_node *node);
int		exec_block(t_ast_node *node);
int		exec_redir(t_ast_node *node);

/*executor*/
void	executor(t_ast_node *node);

/*utils*/
void	set_exit_status(int status);
int		get_exit_status(void);

#endif
