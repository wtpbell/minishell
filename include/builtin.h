/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 18:36:55 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/30 15:31:01 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "parser.h"
# include "env.h"
# include "executor.h"

/*buitin_c.c*/
int		builtin_export(t_ast_node *node);
int		builtin_exit(t_ast_node *node);
int		builtin_cd(t_ast_node *node);
int		builtin_echo(t_ast_node *node);
char	**ft_split_mini(char const *s, char *set);
int		(*is_builtin(char *args))(t_ast_node *node);
#endif
