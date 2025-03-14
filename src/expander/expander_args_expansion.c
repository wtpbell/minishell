/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_args_expansion.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 09:45:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 09:53:22 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

int	contains_expandable_dollar(const char *str, t_ast_node *node, int i)
{
	int	j;
	int	in_single_quotes;

	j = 0;
	in_single_quotes = 0;
	while (str && str[j])
	{
		if (str[j] == '\'')
			in_single_quotes = !in_single_quotes;
		if (str[j] == '$' && !in_single_quotes)
		{
			if (node->arg_quote_types && i < node->argc
				&& node->arg_quote_types[i] == QUOTE_SINGLE)
				return (0);
			return (1);
		}
		j++;
	}
	return (0);
}

int	process_env_expansion(t_ast_node *node, t_env **env_list,
			t_tokenizer *tokenizer, int i)
{
	int	had_env_expansion;

	had_env_expansion = 0;
	handle_env_dollar_expansion(node, env_list, i, &had_env_expansion);
	if (!had_env_expansion)
		handle_dollar_expansion(node, tokenizer, i, &had_env_expansion);
	return (had_env_expansion);
}

void	process_wildcard(t_ast_node *node, int i, int had_env_expansion)
{
	if (has_wildcard(node->args[i]))
	{
		if (had_env_expansion)
			handle_wildcard_with_expansion(node, i);
		else
			handle_wildcard_expansion(node, i);
	}
}

int	should_repeat_expansion(t_ast_node *node, int i,
			int had_env_expansion)
{
	if (had_env_expansion && contains_expandable_dollar(node->args[i], node, i))
		return (1);
	return (0);
}
