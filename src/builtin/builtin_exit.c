/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 23:06:50 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/09 19:12:47 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "common.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

static bool	parse_num(char *arg, long long *num, int *digit_count)
{
	int	i;

	*num = 0;
	*digit_count = 0;
	i = 0;
	while (arg[i] && ft_isdigit(arg[i]))
	{
		if (++(*digit_count) > MAX_STATUS_LEN)
			return (false);
		if ((*num > LLONG_MAX / 10) || (*num == LLONG_MAX / 10 && \
				(arg[i] - '0') > LLONG_MAX % 10))
			return (false);
		*num = (*num * 10) + (arg[i++] - '0');
	}
	return (arg[i] == '\0');
}

static bool	is_within_long_range(char *arg)
{
	long long	num;
	int			sign;
	int			i;
	int			count;

	num = 0;
	sign = 1;
	i = 0;
	count = 0;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	if (!parse_num(arg + i, &num, &count) || count == 0)
		return (false);
	num *= sign;
	return (true);
}
/*
	No Arguments: Exits with status 0 (default).
	Single Numeric Argument: Exits with the given status.
	Single Non-Numeric Argument: Displays an error and exits with status 2.
	Multiple Arguments: Displays an error and does not exit.
*/

int	builtin_exit(t_ast_node *node, t_env **env, t_token *tokens)
{
	char	**args;
	int		exit_status;

	args = node->args;
	exit_status = get_exit_status();
	ft_putendl_fd("exit", STDIN_FILENO);
	if (node->argc > 1)
	{
		if (!(is_within_long_range(args[1])))
		{
			ft_putendl_fd(SHELL_ERROR NUM_ARGS_REQUIRED, STDERR_FILENO);
			exit_shell(2, node, env, tokens);
		}
		else if (node->argc > 2)
		{
			ft_putendl_fd(SHELL_ERROR MANY_ARGS_ERROR, STDERR_FILENO);
			return (1);
		}
		else
			exit_status = ft_atoi(args[1]);
	}
	exit_shell(exit_status, node, env, tokens);
	return (0);
}
