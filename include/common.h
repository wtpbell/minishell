/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 14:56:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/15 21:19:12 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include "executor.h"
# include "parser.h"
# include <signal.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_signal_state
{
	SIG_NONE = 0,
	SIG_RECEIVED_INT = 1,
	SIG_RECEIVED_TERM = 2,
	SIG_RECEIVED_QUIT = 4,
	SIG_HEREDOC_INT = 8
}	t_signal_state;

/*signal_utils1.c */
void			signal_set(t_signal_state state);
int				signal_is_set(t_signal_state state);
void			signal_clear_all(void);

/*signal_handler.c*/
void			interactive_handler(int sig);
void			term_handler(int sig);
void			heredoc_handler(int sig);

/*signal*/
int				setup_signal(int signum, void (*handler)(int));
void			signals_heredoc(void);
void			signals_shell(void);
void			signals_child(void);

void			free_tab(char **tab);
void			free_env(t_env **env);
void			free_exit_memory(t_ast_node *node, \
				t_env **env, t_token *tokens);
void			*mem_realloc(void *ptr, size_t new_size, \
				size_t old_size);
char			**mem_split(char const *str, char *set);
void			exit_shell(int status, t_ast_node *node, \
				t_env **env, t_token *tokens);
void			child_cleanup(t_ast_node *node, char **env_arr);
t_ast_node		*get_root_node(t_ast_node *new_root);

char			*get_custom_prompt(void);
#endif
