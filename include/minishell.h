/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:13:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 10:45:43 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE, // |
	TOKEN_REDIR_IN, // <
	TOKEN_REDIR_OUT, // >
	TOKEN_HEREDOC, // <<
	TOKEN_APPEND, // >>
	TOKEN_AND, // &&
	TOKEN_OR, // ||
	TOKEN_LPAREN, // (
	TOKEN_RPAREN
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	int				here_doc;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

t_token	*tokenize_input(char *input);

#endif
