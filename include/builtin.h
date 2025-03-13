/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 18:36:55 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/13 16:14:22 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include "executor.h"

/*buitin_c.c*/
int		builtin_export(t_ast_node *node, t_env **env, t_token *tokens);
int		builtin_exit(t_ast_node *node, t_env **env, t_token *tokens);
int		builtin_cd(t_ast_node *node, t_env **env, t_token *tokens);
int		builtin_echo(t_ast_node *node, t_env **env, t_token *tokens);
int		(*is_builtin(char *args))(t_ast_node *node, \
		t_env **env, t_token *tokens);
void	env_args_dup(char **split, char **key, char **value);
void	env_args_handler(t_env **env, char **split, char *args);
void	sort_env(t_env **envs);
char	**split_env_var(const char *env_str);

#endif
