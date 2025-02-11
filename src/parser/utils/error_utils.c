/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   error_utils.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <spyun@student.codam.nl>                +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/11 08:54:30 by spyun          #+#    #+#                */
/*   Updated: 2025/02/11 08:54:31 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
