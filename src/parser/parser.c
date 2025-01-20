/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 13:17:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_utils.h"

static t_token	*parse_operator(char **input)
{
	t_token_type	type;
	char			*content;
	int				len;

	len = 1;
	if ((*input)[0] == '|' && (*input)[1] == '|')
		type = TOKEN_OR;
	else if ((*input)[0] == '&' && (*input)[1] == '&')
		type = TOKEN_AND;
	else if ((*input)[0] == '<' && (*input)[1] == '<')
		type = TOKEN_HEREDOC;
	else if ((*input)[0] == '>' && (*input)[1] == '>')
		type = TOKEN_APPEND;
	else if ((*input)[0] == '|')
		type = TOKEN_PIPE;
	else if ((*input)[0] == '<')
		type = TOKEN_REDIR_IN;
	else if ((*input)[0] == '>')
		type = TOKEN_REDIR_OUT;
	else if ((*input)[0] == '(')
		type = TOKEN_LPAREN;
	else if ((*input)[0] == ')')
		type = TOKEN_RPAREN;
	else
		return (NULL);
	if ((type == TOKEN_OR || type == TOKEN_AND ||
		type == TOKEN_HEREDOC || type == TOKEN_APPEND))
		len = 2;
	content = ft_substr(*input, 0, len);
	*input += len;
	return (create_token(content, type));
}

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

t_token	*parse_input(char *input)
{
	t_token	*head;
	t_token	*current;
	char	*start;

	head = NULL;
	while (*input)
	{
		skip_spaces(&input);
		if (!*input)
			break;
		if (is_operator(input))
		{
			current = parse_operator(&input);
			if (!current)
				return (NULL);
			add_token(&head, current);
		}
		else
		{
			start = input;
			while (*input && !is_special_char(*input) && !is_space(*input))
				input++;
			current = create_token(ft_substr(start, 0, input - start), TOKEN_WORD);
			add_token(&head, current);
		}
	}
	return (head);
}
