/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:28:37 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/30 16:07:53 by spyun         ########   odam.nl         */
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

typedef struct s_quote_state
{
	int		in_quote;
	char	quote_char;
}	t_quote_state;

typedef struct s_param_exp
{
	char	*var_name;
	char	*operator;
	char	*word;
}	t_param_exp;

t_token			*tokenize(char *input);

void			init_tokenizer(t_tokenizer *tokenizer, char *input);

t_token			*handle_operator(t_tokenizer *tokenizer);

void			handle_quote(t_tokenizer *tokenizer);
int				is_in_quotes(t_tokenizer *tokenizer);
int				is_special_in_quotes(char c, char quote_char);
t_quote_state	get_quote_state(t_tokenizer *tokenizer);
char			*get_var_value(char *str, int *pos, t_quote_state state);

char			*expand_special_param(const char *param);
char			*handle_extended_expansion(char *var_name, char *operator, char *word);

t_token			*handle_word(t_tokenizer *tokenizer);
char			*handle_expansion(t_tokenizer *tokenizer, char *word);
int				handle_heredoc(char *delimiter, int *heredoc_fd);
char			*handle_braced_expansion(char *str, int *pos,
					t_quote_state state);

t_token			*create_token(char *content, t_token_type type);
void			add_token(t_token **head, t_token *new_token);

t_token_type	get_operator_type(char *input);
int				get_operator_len(t_token_type type);

int				is_operator(char *str);
int				is_special_char(char c);
int				is_quote(char c);
int				validate_quotes(const char *input);

#endif
