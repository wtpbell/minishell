/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:13:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:40:08 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/include/libft.h"
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SHELL_ERROR "minishell: "
# define MANY_ARGS_ERROR "too many arguments"
# define NUM_ARGS_REQUIRED "numeric argument required"
# define NON_EXIST_DIR "Nonexistent directory"
# define NO_FILE_DIR "No such file or directory"
# define NOT_DIR "Is not a directory"
# define IS_DIR "Is a directory"
# define PERMISSION_DENIED "Permission denied"
# define PATH_MAX 4096  //getconf PATH_MAX /
# define DECLARE "declare -x "

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define RESET "\033[0m"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_VAR,
	TOKEN_WILDCARD,
	TOKEN_NEWLINE,
	TOKEN_EOF,
	TOKEN_SUBSHELL,
	TOKEN_ENV,
	TOKEN_BLOCK = TOKEN_SUBSHELL,
	TOKEN_EXEC = TOKEN_WORD,
	TOKEN_CTRL = TOKEN_AND | TOKEN_OR
}	t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_MIXED
}	t_quote_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	t_quote_type	quote_type;
	struct s_token	*next;
}	t_token;

#endif
