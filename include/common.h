/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 14:56:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 17:03:44 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include "executor.h"
# include "parser.h"
# include <signal.h>

typedef enum e_signal_state
{
	SIG_NONE = 0,
	SIG_RECEIVED_INT = 1,
	SIG_RECEIVED_TERM = 2,
	SIG_RECEIVED_QUIT = 4,
	SIG_HEREDOC_INT = 8
} t_signal_state;

extern int g_signal;

/*signal.c */


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

void			signals_init(void);
void			interrupt_w_nl(int sig);
void			interrput_silence(int sig);
void			heredoc_signals(int sig);

char			*get_custom_prompt(void);
#endif
