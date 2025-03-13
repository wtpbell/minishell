/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_expansion_handler.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 16:32:21 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 16:33:32 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

void	handle_env_dollar_expansion(t_ast_node *node, t_env **env_list,
		int i, int *had_expansion)
{
	if (node->args[i][0] == '$' && node->args[i][1])
	{
		if (should_skip_expansion(node, i, 1))
			return ;
		expand_env_var(node, env_list, i);
		*had_expansion = 1;
	}
}

void	handle_dollar_expansion(t_ast_node *node, t_tokenizer *tokenizer,
		int i, int *had_expansion)
{
	if (strchr(node->args[i], '$') != NULL)
	{
		if (should_skip_expansion(node, i, 1))
			return ;
		handle_dollar_in_string(node, tokenizer, i);
		*had_expansion = 1;
	}
}

void	handle_wildcard_with_expansion(t_ast_node *node, int i)
{
	if (node->arg_quote_types && node->arg_quote_types[i] != QUOTE_NONE)
		node->arg_quote_types[i] = QUOTE_NONE;
	handle_wildcard_expansion(node, i);
}
