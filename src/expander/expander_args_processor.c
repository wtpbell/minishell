/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_args_processor.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:27:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 10:59:18 by spyun         ########   odam.nl         */
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

static char	*extract_var_name(char *arg, int *var_len)
{
	char	*var_name;
	int		len;

	len = 0;
	while (arg[len] && (ft_isalnum(arg[len]) || arg[len] == '_'))
		len++;
	var_name = ft_substr(arg, 0, len);
	*var_len = len;
	return (var_name);
}

static void	handle_regular_env_var(t_ast_node *node, t_env **env_list, int i)
{
	char	*var_name;
	char	*env_value;
	char	*result;
	char	*rest_of_arg;
	int		var_len;

	var_name = extract_var_name(node->args[i] + 1, &var_len);
	rest_of_arg = ft_strdup(node->args[i] + 1 + var_len);
	env_value = get_env_value(*env_list, var_name);
	if (env_value)
		result = ft_strdup(env_value);
	else
		result = ft_strdup("");
	free(var_name);
	if (rest_of_arg && *rest_of_arg)
		result = join_and_free(result, rest_of_arg);
	free(rest_of_arg);
	free(node->args[i]);
	node->args[i] = result;
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

static void	handle_wildcard_expansion(t_ast_node *node, int i)
{
	if (should_skip_expansion(node, i, 0)
		&& !is_mixed_quote_wildcard(node->args[i], node->arg_quote_types[i]))
		return ;
	if (node->arg_quote_types && node->arg_quote_types[i] == QUOTE_MIXED)
	{
		process_mixed_wildcard(node, i);
		return ;
	}
	process_wildcard_arg(node, i);
}

void	handle_arg_expansion(t_ast_node *node, t_env **env_list,
		t_tokenizer *tokenizer, int i)
{
	if (node->args[i][0] == '$' && node->args[i][1])
	{
		if (should_skip_expansion(node, i, 1))
			return ;
		expand_env_var(node, env_list, i);
		if (strchr(node->args[i], '$') != NULL)
			handle_dollar_in_string(node, tokenizer, i);
	}
	else if (strchr(node->args[i], '$') != NULL)
	{
		if (should_skip_expansion(node, i, 1))
			return ;
		handle_dollar_in_string(node, tokenizer, i);
	}
	else if (has_wildcard(node->args[i]))
		handle_wildcard_expansion(node, i);
}
