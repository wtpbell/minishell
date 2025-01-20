/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:12:53 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 13:12:56 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token_utils.h"

t_token	*create_token(char *content, t_token_type type)
{
	t_token	*new_token;

	if (!content)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = content;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

int	is_operator(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '|' || *str == '<' || *str == '>' ||
		*str == '(' || *str == ')' ||
		(*str == '&' && *(str + 1) == '&') ||
		(*str == '|' && *(str + 1) == '|'))
		return (1);
	return (0);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' ||
			c == '(' || c == ')' || c == '&' ||
			c == '\'' || c == '\"' || c == ' ' ||
			c == '\t' || c == '\n');
}

void	skip_spaces(char **input)
{
	while (**input && (**input == ' ' || **input == '\t'))
		(*input)++;
}
