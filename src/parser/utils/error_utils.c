/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 08:54:30 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/28 16:15:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executor.h"

/* Handle logic error */
t_ast_node	*handle_logic_error(void)
{
	ft_putendl_fd("minishell: syntax error near unexpected token",
		STDERR_FILENO);
	return (NULL);
}

/* Handle group error */
t_ast_node	*handle_group_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (NULL);
}

void	handle_redirection_error(t_token *current)
{
	if (!current->next)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
	else if (current->next->type == TOKEN_PIPE)
		ft_putendl_fd("minishell: syntax error near unexpected token `|'",
			STDERR_FILENO);
	else
		ft_putendl_fd("minishell: syntax error near unexpected token",
			STDERR_FILENO);
}
