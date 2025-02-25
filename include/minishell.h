/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:13:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/17 16:52:42 by bewong        ########   odam.nl         */
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
# include <readline/readline.h>
# include <readline/history.h>

# define SHELL_ERROR "minishell: "
# define MANY_ARGS_ERROR "Too many argument!"
# define NON_EXIST_DIR "Nonexistent directory"
# define PATH_MAX 4096  //getconf PATH_MAX /
# define DECLARE "declare -x "

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define RESET "\033[0m"

extern int	g_exit_status;

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

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_token_type	type;
}	t_token;

void	print_banner(void);

void	print_banner(void);

#endif
