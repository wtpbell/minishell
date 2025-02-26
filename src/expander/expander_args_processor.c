/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_args_processor.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:27:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/26 14:40:42 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

/* Expands environment variables (e.g., $VAR -> VAR value) */
static void	expand_env_var(t_ast_node *node, t_env **env_list, int i)
{
	char	*var_name;
	char	*env_value;

	var_name = node->args[i] + 1;
	env_value = get_env_value(*env_list, var_name);
	if (env_value)
	{
		free(node->args[i]);
		node->args[i] = mem_strdup(env_value);
	}
	else
	{
		free(node->args[i]);
		node->args[i] = mem_strdup("");
	}
}

/* Handles argument expansion when a $ is inside the string */
static void	handle_dollar_in_string(t_ast_node *node, t_tokenizer *tokenizer,
		int i)
{
	char	*expanded_arg;

	expanded_arg = handle_expansion(tokenizer, node->args[i]);
	if (expanded_arg)
	{
		free(node->args[i]);
		node->args[i] = expanded_arg;
	}
}

/* Process expansion for a single argument */
void	handle_arg_expansion(t_ast_node *node, t_env **env_list,
		t_tokenizer *tokenizer, int i)
{
	if (node->args[i][0] == '$' && node->args[i][1])
	{
		if (should_skip_expansion(node, i, 1))
			return ;
		expand_env_var(node, env_list, i);
	}
	else if (strchr(node->args[i], '$') != NULL)
	{
		if (should_skip_expansion(node, i, 1))
			return ;
		handle_dollar_in_string(node, tokenizer, i);
	}
	else if (has_wildcard(node->args[i]))
	{
		if (should_skip_expansion(node, i, 0))
			return ;
		expand_wildcards(node);
	}
}
