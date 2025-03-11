/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 14:56:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/11 15:21:05 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include "executor.h"
# include "parser.h"

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

/*signal*/
void			signals_init(void);
void			interrupt_w_nl(int sig);
void			interrput_silence(int sig);
void			heredoc_signals(int sig);

void			print_banner(void);
char			*get_custom_prompt(void);
#endif
