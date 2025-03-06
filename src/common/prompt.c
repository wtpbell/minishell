/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 15:38:39 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/06 16:13:01 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*get_relative_path(char *cwd)
{
	char	*home_dir;
	char	*relative_path;
	size_t	home_len;

	home_dir = getenv("HOME");
	if (!home_dir)
		return (ft_strdup(cwd));
	home_len = ft_strlen(home_dir);
	if (ft_strncmp(cwd, home_dir, home_len) == 0)
	{
		relative_path = malloc(ft_strlen(cwd) - home_len + 2);
		if (!relative_path)
			return (ft_strdup(cwd));
		relative_path[0] = '~';
		ft_strlcpy(relative_path + 1, cwd + home_len,
			ft_strlen(cwd) - home_len + 1);
		return (relative_path);
	}
	return (ft_strdup(cwd));
}

static char	*join_three_strings(char *s1, char *s2, char *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	ft_strlcat(result, s3, len1 + len2 + len3 + 1);
	return (result);
}

static char	*create_prompt_string(char *path)
{
	char	*result;

	result = join_three_strings(path, "", "$ ");
	if (!result)
		return (ft_strdup("minishell$ "));
	return (result);
}

char	*get_custom_prompt(void)
{
	char	*cwd;
	char	*relative_path;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup(".");
	relative_path = get_relative_path(cwd);
	prompt = create_prompt_string(relative_path);
	free(cwd);
	free(relative_path);
	return (prompt);
}
