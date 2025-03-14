/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:28:37 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 09:20:57 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_tokenizer
{
	char			*input;
	t_token			*head;
	int				position;
	int				in_quote;
	char			quote_char;
	t_quote_type	current_quote_type;
}	t_tokenizer;

typedef struct s_quoted_result
{
	char			*content;
	t_quote_type	quote_type;
}	t_quoted_result;

typedef struct s_match_state
{
	int	i;
	int	j;
	int	star_idx;
	int	str_star_idx;
}	t_match_state;

/* Main tokenization functions */
t_token			*tokenize(char *input);
void			init_tokenizer(t_tokenizer *tokenizer, char *input);
t_token			*create_token(char *content, t_token_type type);
void			add_token(t_token **head, t_token *new_token);
void			free_tokens(t_token *token);

/* Token type handlers */
t_token			*handle_operator(t_tokenizer *tokenizer);
t_token			*handle_word(t_tokenizer *tokenizer);
t_token			*handle_wildcard_token(const char *str);
int				match_pattern(const char *pattern, const char *string);

/* Quote handling */
void			handle_quote(t_tokenizer *tokenizer);
int				validate_quotes(const char *input);
t_quote_type	quote_type_select(t_quote_type current_type, char quote);

/* Helper functions */
t_token_type	get_operator_type(char *input);
int				get_operator_len(t_token_type type);
int				is_operator(char *str);
int				is_quote(char c);
int				has_wildcard(const char *str);
int				is_valid_position(t_tokenizer *tokenizer);
char			*join_words(char *s1, char *s2);
char			*handle_quote_in_word(t_tokenizer *tokenizer, char *result,
					t_quote_type *current_quote_type);
char			*handle_char_in_word(t_tokenizer *tokenizer, char *result);
t_quoted_result	*extract_quoted_content(t_tokenizer *tokenizer, char quote,
					t_quote_type current_quote_type);
char			*handle_special_wildcard(t_tokenizer *tokenizer);
int				is_wildcard_after_quote(t_tokenizer *tokenizer);
#endif
