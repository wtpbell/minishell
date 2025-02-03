/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/03 15:37:32 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include "builtin.h"
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
void error(char *word, char *msg);

/*execute_tree*/
int		exec_cmd(t_ast_node *node);
int		exec_pipe(t_ast_node *node);
int		exec_ctrl(t_ast_node *node);
int		exec_block(t_ast_node *node);
int		exec_redir(t_ast_node *node);

/*executor*/
void	executor(t_ast_node *node);
int		executor_status(t_ast_node *node);

/*utils*/
void	set_exit_status(int status);
int		get_exit_status(void);
void	sort_env(t_env **envs);
char	**ft_split_mini(char const *s, char *set);

/*utils2*/

void	append_cwd(t_ast_node *node);
int		check_cmd(t_ast_node *node);

/*utils3*/
int		check_paths(char *full_path);

#endif
