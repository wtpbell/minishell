/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:28:37 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 15:48:31 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_tokenizer
{
	char	*input;
	t_token	*head;
	int		position;
	int		in_quote;
	char	quote_char;
}	t_tokenizer;

void			init_tokenizer(t_tokenizer *tokenizer, char *input);

t_token			*handle_operator(t_tokenizer *tokenizer);

void			handle_quote(t_tokenizer *tokenizer);
int				is_in_quotes(t_tokenizer *tokenizer);

t_token			*handle_word(t_tokenizer *tokenizer);

t_token			*create_token(char *content, t_token_type type);
void			add_token(t_token **head, t_token *new_token);

t_token_type	get_operator_type(char *input);
int				get_operator_len(t_token_type type);

t_token			*tokenize(char *input);
#endif
