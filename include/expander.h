/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 12:13:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/13 17:54:10 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "common.h"
# include "minishell.h"
# include "parser.h"

/*expander*/
void	expand_vars(t_ast_node *node);
void	expander(t_ast_node *node);

/*expand_exec*/
bool	is_expand_char(char c);
void	expand_exec_vars(t_ast_node *node);

/*expand_redir*/
void	expand_redir_vars(t_redirection *r);

/*expand_utils*/
void	add_to_args(char ***expanded, char *str, int *count, bool splited);
int		count_words(char **words);

/*expand_utils2*/
char	*append_vars(char *appended, char *str, int *pos);
char	*append_regular(char *appended, char *str, int *pos, char *set);
char	*expand_var(char *var, int *pos);
char	*get_var_values(char *var, int len);

/*expand_quotes*/
char	*expand_double_quote(char *str, int *i);
char	*expand_single_quote(char *str, int *i);

/*expand_heredoc*/
void	expand_heredoc(t_redirection *r);

#endif
