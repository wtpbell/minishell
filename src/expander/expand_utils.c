/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 11:09:40 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/13 17:57:27 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "parser.h"
#include "expander.h"


int	count_words(char **words)
{
	int	len;
	
	len = 0;
	while (words[len])
		len++;
	return (len);
}

static char	**add_empty_str(char **words, int *count)
{
	char	**tmp;

	tmp = (char **)mem_alloc(sizeof(char *) * 2);
	tmp[0] = mem_strdup("");
	tmp[1] = NULL;
	*count = 1;
	free_alloc(words);
	return (tmp);
}

static void	add_n_split(char ***expanded, char *str, int *count)
{
	char	**new_args;
	char	**words;
	int		nbr_words;
	int		i;

	words = mem_split(str, "\t\f\v\r");
	if (!words)
		return ;
	nbr_words = count_words(words);
	if (nbr_words == 0)
		words = add_empty_str(words, &nbr_words);
	new_args = (char **)mem_alloc(sizeof(char *) * ((*count) + nbr_words + 1));
	if (!new_args)
	{
		free_alloc(words);
		return;
	}
	i = -1;
	while (++i < (*count))
		new_args[i] = (*expanded)[i];
	i = -1;
	while (++i < nbr_words)
		new_args[(*count) + i] = words[i];
	new_args[(*count) + nbr_words] = NULL;
	free_alloc(words);
	*count += nbr_words;
	free_alloc(*expanded);
	*expanded = new_args;
}

static void	add_n_append(char ***expanded, char *str, int *count)
{
	char	**new_args;
	int		i;

	if (!str)
		return ;
	new_args = (char **)mem_alloc(sizeof(char *) * ((*count) + 2));
	if (!new_args)
		return ;
	i = -1;
	while (++i < (*count))
		new_args[i] = (*expanded)[i];
	new_args[(*count)] = str;
	new_args[(*count) + 1] = NULL;
	free_alloc(*expanded);
	*expanded = new_args;
	(*count)++;
}

void	add_to_args(char ***expanded, char *str, int *count, bool splited)
{
	if (!expanded || !str || !count)
		return ;
	if (splited)
		add_n_split(expanded, str, count);
	else
		add_n_append(expanded, str, count);
}

