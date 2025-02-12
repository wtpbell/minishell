/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_exec.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 12:00:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/12 12:18:27 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

/*
	This function checks if a character is an expansion-related character:
		$ -> Variable expansion
		" -> Double quotes (can expand variables inside)
		' -> Single quotes (prevents expansion)
		' ' -> Space (detect token separation)
*/
bool	is_expand_char(char c)
{
	return (c == '$' || c == '"' || c == '\'' || c == ' ');
}

/* This function expands a single argument node->args[i] */
static char	*expand_args(t_ast_node *node, int i, bool *splited)
{
	char	*appended;
	int		k;

	*splited = 1;
	appended = NULL;
	k = 0;
	while (node->args[i][k])
	{
		if (is_expand_char(node->args[i][k]))
		{
			if (node->args[i][k] == '\'' || node->args[i][k] == '"')
				*splited = 0;
			appended = append_vars(appended, node->args[i] + k, &k);
			if (!appended)
				return (NULL);
		}
		else
			appended = append_regular(appended, node->args[i] + k, &k, "'\"$");
	}
	return (appended);
}

/*
	This function applies the above function to all arguments, expanding varaiables
	and handling quotes
 */
void	expand_exec_vars(t_ast_node *node)
{
	char	**expanded_args;
	int		expanded_argc;
	bool	splited;
	char	*expanded_str;
	int		i;

	if (!node || !node->args)
		return ;
	expanded_args = NULL;
	expanded_argc = 0;
	i = 0;
	while (i < node->argc)
	{
		expanded_str = expand_args(node, i, &splited);
		if (expanded_str)
			add_to_args(&expanded_args, expanded_str, &expanded_argc, splited);
		i++;
	}
	node->args = expanded_args;
	node->argc = expanded_argc;
}
