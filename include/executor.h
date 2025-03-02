/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/02 21:15:21 by bewong        ########   odam.nl         */
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
# define ERR_NO_FILE 127
# define ERR_NOT_DIR 126
# define ERR_ACCESS EXIT_FAILURE
# define ERR_MALLOC EXIT_FAILURE
# define ERR_CHDIR EXIT_FAILURE
# define ERR_ENV EXIT_FAILURE

typedef struct s_heredoc_data
{
	char	*line;
	char	*delimiter;
	int		fd;
	t_env	*env_list;
	int		should_expand;
}	t_heredoc_data;

typedef struct s_child_info
{
	int	input;
	int	output;
	int	new_input;
}	t_child_info;


/*error*/
void	error(char *word, char *msg);
void	error_heredoc(char *delimiter);

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
pid_t launch_pipe(int input, int pipe_fd[2], t_ast_node *temp_node, t_env **env);
pid_t	spawn_process(int input, int pipe_fd[2], \
		t_ast_node *node, t_env **env);
void	redirect_io(int input, int output, int new_input);

/*execute_heredoc*/
void	handle_all_heredocs(t_redir *redir, int saved_fd[2]);

/*execute_redir*/
void	launch_redir(t_redir *current_redir, int saved_fd[2]);
void	restore_redirection(int saved_fd[2]);

/*utils*/
void	set_exit_status(int status);
int		get_exit_status(void);
void	sort_env(t_env **envs);
int		get_flags(t_token_type type);
int		get_redir_fd(t_token_type type);
void	cleanup_heredocs(t_redir *redir);

/*utils2*/
void	append_cwd(t_ast_node *node);
int		check_cmd(t_ast_node *node, t_env **env);

/*utils3*/
int		check_paths(char *full_path);

/*heredoc utils*/
char	*gen_filename(void);
int		write_expanded_line(char *expanded_line, int fd);
int		process_line(t_heredoc_data *data);
#endif
