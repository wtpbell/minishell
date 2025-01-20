/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:30:39 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 13:20:19 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_token_type(char *str)
{
	if (!str)
		return (TOKEN_WORD);
	if (str[0] == '|' && !str[1])
		return (TOKEN_PIPE);
	if (str[0] == '<')
	{
		if (str[1] == '<' && str[1])
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>' && str[1])
			return (TOKEN_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

static t_token	*process_tokens(char **tokens)
{
	t_token	*head;
	t_token	*current;
	int		i;

	i = 0;
	head = NULL;
	while (tokens[i])
	{
		if (!head)
		{
			head = create_token(tokens[i], get_token_type(tokens[i]));
			current = head;
		}
		else
		{
			current->next = create_token(tokens[i], get_token_type(tokens[i]));
			current = current->next;
		}
		i++;
	}
	return (head);
}

static void	free_token_array(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}


t_token	*tokenize_input(char *input)
{
	t_token	*head;
	char	**tokens;

	if (!input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	head = process_tokens(tokens);
	free_token_array(tokens);
	return (head);
}
