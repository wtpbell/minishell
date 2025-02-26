/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 12:13:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/26 13:35:30 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "common.h"
# include "minishell.h"
# include "parser.h"

/*expander*/
void	expander(t_ast_node *node, t_env **env_list);

/*expand_exec*/
void	expand_wildcards(t_ast_node *node);
char	**get_matching_files(const char *pattern, int *num_matches);
char	*handle_expansion(t_tokenizer *tokenizer, const char *arg);
#endif
