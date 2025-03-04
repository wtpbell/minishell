/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 14:56:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/04 21:45:48 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "executor.h"


void			free_tab(char **tab);
void			free_env(t_env **env);
void			free_exit_memory(t_ast_node *node, t_env **env, t_token *tokens);
void			*mem_realloc(void *ptr, size_t new_size, size_t old_size);
char			**mem_split(char const *str, char *set);
void			free_split(char **arr, int i);

/*signal*/

void			signals_init(void);
void			interrupt_w_msg(int sig);
void			interrput_silence(int sig);
int				*heredoc_error(void);
void			heredoc_signals(int sig);
#endif
