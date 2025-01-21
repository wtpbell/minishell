#ifndef MINISHELL_H
#define MINISHELL_H

# define PATH_MAX 1024

# include <errno.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/wait.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPED,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_EPAREN,
	TOKEN_NEWLINE,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}	t_token;


typedef struct s_redir
{
	char	*infile;
	char	*outfile;
	int		here_doc;
	int		append;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	char			***env_ptr;
	int				*exitcode;
	struct s_cmd	*next;
	t_redir			redir;
}	t_cmd;

typedef struct s_minishell
{
	t_token			*env_list;
	t_token			*token_list;
	t_cmd			*cmd;
}	t_minishell;

#endif
