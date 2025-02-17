/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/17 16:53:45 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include "builtin.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MAX_STATUS_LEN 20
# define EXIT_ERROR_CODE 255

/*error*/
void	error(char *word, char *msg);

/*execute_tree*/
int		exec_cmd(t_ast_node *node, t_env **env);
int		exec_pipe(t_ast_node *node, t_env **env);
int		exec_ctrl(t_ast_node *node, t_env **env);
int		exec_block(t_ast_node *node, t_env **env);
int		exec_redir(t_ast_node *node, t_env **env, t_redir *redir);

/*execute_process*/
void	child(t_ast_node *node, t_env **env);
int		parent(t_ast_node *node);

/*executor*/
void	executor(t_ast_node *node, t_env **env);
int		executor_status(t_ast_node *node, t_env **env);

/*execute_pipe*/
size_t	count_pipes(t_ast_node *node);
pid_t	launch_pipe(t_ast_node *node, t_env **env);
pid_t	spawn_process(int input, int pipe_fd[2], \
		t_ast_node *node, t_env **env);
void	child_process(t_ast_node *node, int input, \
		int output, int new_input, t_env **env);
void	redirect_io(int input, int output, int new_input);

/*utils*/
void	set_exit_status(int status);
int		get_exit_status(void);
void	sort_env(t_env **envs);
int		get_redir_flags(t_token_type type);
int		get_redir_fd(t_token_type type);
/*utils2*/
void	append_cwd(t_ast_node *node);
int		check_cmd(t_ast_node *node, t_env **env);

/*utils3*/
int		check_paths(char *full_path);

#endif
