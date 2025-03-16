/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 10:13:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/16 19:20:46 by bewong        ########   odam.nl         */
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
	char			*line;
	char			*delimiter;
	int				fd;
	t_env			*env_list;
	int				should_expand;
	t_quote_type	quote_type;
}	t_heredoc_data;

typedef struct s_child_info
{
	int			input;
	int			output;
	int			new_input;
	t_token		*tokens;
	int			saved_stdin;
}	t_child_info;

/*error*/
void	error(char *word, char *msg);
void	error_heredoc(char *delimiter);

/*execute_tree*/
int		exec_cmd(t_ast_node *node, t_env **env, t_token *tokens);
int		exec_pipe(t_ast_node *node, t_env **env, t_token *tokens);
int		exec_ctrl(t_ast_node *node, t_env **env, t_token *tokens);
int		exec_block(t_ast_node *node, t_env **env, t_token *tokens);
int		exec_redir(t_ast_node *node, t_env **env, t_token *tokens, bool error_);

/*execute_process*/
void	child(t_ast_node *node, t_env **env);

/*executor*/
void	executor(t_ast_node *node, t_env **env, t_token *toekns);
int		executor_status(t_ast_node *node, t_env **env, \
		t_token *tokens, bool error);

/*execute_pipe*/
pid_t	launch_pipe(t_child_info *child, int pipe_fd[2], \
		t_ast_node *temp_node, t_env **env);
pid_t	spawn_process(t_child_info *child, int pipe_fd[2], \
		t_ast_node *node, t_env **env);
void	redirect_io(int input, int output, int new_input);
t_redir	*get_last_heredoc(t_redir *curr);

/*execute_heredoc*/
void	handle_all_heredocs(t_redir *redir, int saved_fd[2]);

/*execute_redir*/
bool	launch_redir(t_redir *current_redir, int saved_fd[2], bool error_);
void	restore_redirection(int saved_fd[2]);
void	handle_redirections(t_redir *curr, int saved_fd[2], int error_);
void	handle_regular_redirection(t_redir *current_redir, \
			int saved_fd[2], bool error_);
void	handle_heredoc_redirection(t_redir *current_redir, int saved_fd[2]);

/*utils*/
void	set_exit_status(int status);
int		get_exit_status(void);
void	cleanup_heredocs(t_redir *redir);

/*utils2*/
void	append_cwd(t_ast_node *node);
int		check_cmd(t_ast_node *node, t_env **env);

/*utils3*/
int		validate_path(char *full_path);

/*heredoc utils*/
char	*gen_filename(void);
int		process_line(t_heredoc_data *data);

/*execute_cmd.c*/
int		launch_external_cmd(t_ast_node *node, t_env **env, t_token *tokens);
int		is_kill_zero(t_ast_node *node);

/*pipe_utils.c*/
void	redirect_io(int input, int output, int new_input);
void	child_init(t_child_info *child, int input, t_token *tokens);
pid_t	final_process(t_child_info *child, t_ast_node *temp, t_env **env);

/*wait_utils.c*/
int		wait_for_child(void);
int		wait_for_pid(pid_t pid);
void	wait_for_remain(void);
int		process_exit_status(int status_);
#endif
