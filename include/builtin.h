/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 18:36:55 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/23 18:51:38 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parser.h"
# include "env.h"

int		builtin_export(t_ast_node *node, t_env **env);
int		builtin_exit(t_ast_node *node);
int		builtin_cd(t_ast_node *node, t_env **env);
int		builtin_echo(t_ast_node *node);

#endif
