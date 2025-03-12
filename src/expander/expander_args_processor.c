/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_args_processor.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:27:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 19:42:49 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

static void	handle_exit_status_expansion(t_ast_node *node, int i)
{
	char	*status;
	char	*result;

	status = ft_strdup(get_env_value(*get_env_list(), "?"));
	if (!status)
		status = ft_strdup("0");
		
	if (node->args[i][2] != '\0')
	{
		result = ft_strjoin(status, node->args[i] + 2);
		free(status);
		free(node->args[i]);
		node->args[i] = result;
	}
	else
	{
		free(node->args[i]);
		node->args[i] = status;
	}
}

static void	handle_regular_env_var(t_ast_node *node, t_env **env_list, int i)
{
	char	*var_name;
	char	*env_value;

	var_name = node->args[i] + 1;
	env_value = get_env_value(*env_list, var_name);
	if (env_value)
	{
		free(node->args[i]);
		node->args[i] = ft_strdup(env_value);
	}
	else
	{
		free(node->args[i]);
		node->args[i] = ft_strdup("");
	}
}

static void	expand_env_var(t_ast_node *node, t_env **env_list, int i)
{
	if (node->args[i][1] == '?')
		handle_exit_status_expansion(node, i);
	else
		handle_regular_env_var(node, env_list, i);
}

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
		if (should_skip_expansion(node, i, 0)
			&& !is_mixed_quote_wildcard(node->args[i],
				node->arg_quote_types[i]))
			return ;
		if (node->arg_quote_types && node->arg_quote_types[i] == QUOTE_MIXED)
		{
			process_mixed_wildcard(node, i);
			return ;
		}
		process_wildcard_arg(node, i);
	}
}
