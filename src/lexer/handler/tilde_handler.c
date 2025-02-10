/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilde_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:43:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/04 10:54:59 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Return the value of the HOME environment variable */
static char	*get_home_directory(void)
{
	char	*home;

	/* change to get_env */
	home = getenv("HOME");
	if (!home)
		return (NULL);
	return (ft_strdup(home));
}

/* ~ Handle path expansion (~/ -> $HOME/ or ~ -> $HOME) */
char	*handle_tilde_expansion(char *path)
{
	char	*result;
	char	*home;

	if (!path || path[0] != '~')
		return (ft_strdup(path));
	if (path[1] != '/' && path[1] != '\0')
		return (ft_strdup(path));
	home = get_home_directory();
	if (!home)
		return (ft_strdup(path));
	if (path[1] == '\0')
		return (home);
	result = ft_strjoin(home, path + 1);
	free(home);
	return (result);
}
