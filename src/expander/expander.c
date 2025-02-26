/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 10:35:01 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/26 13:34:26 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

// Expands environment variables (e.g., $VAR -> VAR value)
static void	expand_env_var(t_ast_node *node, t_env **env_list, int i)
{
	char	*var_name;
	char	*env_value;

	var_name = node->args[i] + 1;  // Skip the '$' character
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

// Handles argument expansion when a $ is inside the string
static void	handle_dollar_in_string(t_ast_node *node, t_tokenizer *tokenizer, int i)
{
	char	*expanded_arg;

	expanded_arg = handle_expansion(tokenizer, node->args[i]);
	if (expanded_arg)
	{
		free(node->args[i]);
		node->args[i] = expanded_arg;
	}
}

// Expands wildcards if present in the argument
static void	handle_wildcards(t_ast_node *node)
{
	expand_wildcards(node);
}

// Main expander function with the logic split
void expander(t_ast_node *node, t_env **env_list)
{
	int i;
	t_tokenizer tokenizer;
	if (!node || !node->args)
		return;
	ft_memset(&tokenizer, 0, sizeof(t_tokenizer));
	i = 0;
	while (i < node->argc && node->args[i])
	{
		if (node->args[i][0] == '$' && node->args[i][1])
		{
			if (node->arg_quote_types && node->arg_quote_types[i] == QUOTE_SINGLE)
			{
				i++;
				continue;
			}
			expand_env_var(node, env_list, i);
		}
		else if (strchr(node->args[i], '$') != NULL)
		{
			if (node->arg_quote_types && node->arg_quote_types[i] == QUOTE_SINGLE)
			{
				printf("Skipping dollar expansion for '%s' due to single quotes\n", node->args[i]);
				i++;
				continue;
			}
			handle_dollar_in_string(node, &tokenizer, i);
		}
		else if (has_wildcard(node->args[i]))
		{
			if (node->arg_quote_types &&(node->arg_quote_types[i] == QUOTE_SINGLE
			|| node->arg_quote_types[i] == QUOTE_DOUBLE))
			{
				i++;
				continue;
			}
			handle_wildcards(node);
		}
		i++;
	}
}
