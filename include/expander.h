/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 12:13:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/12 12:32:10 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "common.h"
# include "minishell.h"
# include "parser.h"

/*expand_exec*/
bool	is_expand_char(char c);
void	expand_exec_vars(t_ast_node *node);

/*expand_redir*/

/*expand_utils*/
void	add_to_args(char ***expanded, char *str, int *count, bool splited);

/*expand_utils2*/
char	*append_regular(char *appended, char *str, int *pos, char *set);

/*expand_quotes*/
char	*expand_double_quote(char *str, int *i);
char	*expand_single_quote(char *str, int *i);

#endif
