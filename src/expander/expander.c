/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 10:35:01 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/27 10:05:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

/* Checks if expansion should be skipped based on quote types */
int	should_skip_expansion(t_ast_node *node, int i, int dollar_exp)
{
	if (!node->arg_quote_types)
		return (0);
	if (dollar_exp && node->arg_quote_types[i] == QUOTE_SINGLE)
		return (1);
	if (!dollar_exp && (node->arg_quote_types[i] == QUOTE_SINGLE
			|| node->arg_quote_types[i] == QUOTE_DOUBLE))
		return (1);
	return (0);
}

static void	expander_process_args(t_ast_node *node, t_env **env_list,
			t_tokenizer *tokenizer)
{
	int	i;

	i = 0;
	while (i < node->argc && node->args[i])
	{
		handle_arg_expansion(node, env_list, tokenizer, i);
		i++;
	}
}

/* Main expander function */
void	expander(t_ast_node *node, t_env **env_list)
{
	t_tokenizer	tokenizer;

	if (!node || !node->args)
		return ;
	ft_memset(&tokenizer, 0, sizeof(t_tokenizer));
	expander_process_args(node, env_list, &tokenizer);
}
