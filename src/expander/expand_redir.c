/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_redir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 12:00:39 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/13 17:59:37 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "parser.h"
#include "expander.h"

static char	**expand_filenames(t_redirection *r)
{
	int		i;
	bool	splited;
	char	*appended;
	char	**words;
	int		size;

	splited = 1;
	words = NULL;
	size = 0;
	i = 0;
	appended = NULL;
	while (r->file[i])
	{
		if (is_expand_char(r->file[i]))
		{
			if (r->file[i] == '\'' || r->file[i] == '"')
				splited = 0;
			appended = append_vars(appended, r->file + i, &i);
		}
		else
			appended = append_regular(appended, r->file + i, &i, "'\"$");
	}
	if (appended)
		add_to_args(&words, appended, &size, splited);
	return (words);
}

void	expand_redir_vars(t_redirection *r)
{
	char	**words;

	if (r->type == TOKEN_HEREDOC)
		return (expand_heredoc(r));
	words = expand_filenames(r);
	if (!words || count_words(words) != 1)
	{
		error(r->file, "redirect");
		free_alloc(r->file);
		r->file = NULL;
	}
	else
	{
		free_alloc(r->file);
		r->file = words[0];
	}
	free_alloc(words);
}
