/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 18:36:55 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/23 19:36:33 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include "executor.h"

/*buitin_c.c*/
int		builtin_export(t_ast_node *node, t_env **env);
int		builtin_exit(t_ast_node *node, t_env **env);
int		builtin_cd(t_ast_node *node, t_env **env);
int		builtin_echo(t_ast_node *node, t_env **env);
int		(*is_builtin(char *args))(t_ast_node *node, t_env **);
#endif
