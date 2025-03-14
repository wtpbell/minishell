/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:46:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 14:23:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"
# include <fcntl.h>

typedef struct s_redir
{
	t_token_type			type;
	char					*file;
	char					*delimiter;
	char					*heredoc_file;
	int						fd;
	int						flags;
	t_quote_type			quote_type;
	int						heredoc_processed;
	struct s_redir			*next;
}	t_redir;

typedef struct s_last_redir
{
	t_redir	*in;
	t_redir	*out;
	t_redir	*heredoc;
	t_redir	*append;
}	t_last_redir;

typedef struct s_ast_node
{
	t_token_type		type;
	char				**args;
	t_quote_type		*arg_quote_types;
	int					argc;
	t_redir				*redirections;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	int					is_subshell;
}	t_ast_node;

typedef enum e_cmd_valid_error
{
	VALID_SUCCESS,
	VALID_EMPTY_CMD,
	VALID_INVALID_REDIR,
	VALID_MISSING_FILENAME,
	VALID_SYNTAX_ERROR,
	VALID_TOO_MANY_ARGS,
}	t_cmd_valid_error;

typedef enum e_syntax_error
{
	SYNTAX_OK,
	SYNTAX_UNEXPECTED_TOKEN,
	SYNTAX_MISSING_TOKEN,
	SYNTAX_INVALID_COMBINATION,
	SYNTAX_UNMATCHED_PARENTHESES,
	SYNTAX_INVALID_SEQUENCE,
	SYNTAX_INVALID_SUBSHELL,
	SYNTAX_NESTED_TOO_DEEP,
	SYNTAX_INVALID_COMMAND
}	t_syntax_error;

typedef struct s_arg_data
{
	char			**new_args;
	t_quote_type	*new_quote_types;
	int				args_len;
	t_quote_type	quote_type;
}	t_arg_data;

/* Main parsing functions */
t_ast_node			*parse(t_token *tokens);
t_ast_node			*parse_complete_bonus(t_token **token);
t_ast_node			*parse_pipeline(t_token **token);
t_ast_node			*parse_command(t_token **token);
t_ast_node			*parse_group(t_token **token);
t_ast_node			*parse_redirection(t_token **token);
t_ast_node			*parse_pipe_sequence(t_token **token);
t_ast_node			*parse_tokens_to_ast(t_token **tokens);
t_ast_node			*validate_ast(t_ast_node *root);

/* AST node manipulation */
t_ast_node			*create_ast_node(t_token_type type);
t_redir				*init_redir_node(t_token_type type, char *file,
						t_quote_type quote_type);
void				set_redir_flags_and_fd(t_redir *redir, t_token_type type);
void				add_arg_to_node(t_ast_node *node, char *arg,
						t_quote_type quote_type);
void				free_ast(t_ast_node *node);
void				free_redirections(t_redir *redir);
int					is_command_separator(t_token *token);

/* Logic operation handling */
t_ast_node			*parse_command_sequence(t_token **token,
						t_token_type end_type);
t_ast_node			*handle_logic_operation(t_token **token,
						t_ast_node *left);
int					is_logic_operator(t_token *token);
t_ast_node			*create_logic_node(t_token **token);
t_ast_node			*handle_logic_error(void);
t_ast_node			*handle_pipe_right(t_token **token, t_ast_node *left);
void				add_redirection(t_ast_node *node, t_token_type type,
						char *file, t_quote_type quote_type);
t_ast_node			*create_pipe_node(t_ast_node *left, t_ast_node *right);
t_ast_node			*handle_redirection_in_pipe(t_ast_node *left,
						t_token **token);
t_ast_node			*handle_pipe_redirection(t_token **token);

/* Syntax validation */
t_cmd_valid_error	validate_command_syntax(t_ast_node *node);
t_syntax_error		validate_syntax_tree(t_ast_node *root);
t_syntax_error		validate_redir_syntax(t_ast_node *node);
t_syntax_error		validate_subshell_syntax(t_ast_node *node);
int					validate_parentheses(t_token *tokens);
int					is_valid_command_name(const char *cmd);
int					is_valid_token_sequence(t_token *tokens);
int					validate_first_token(t_token *token);
int					is_valid_filename_token(t_token *token);
void				handle_redirection_error_message(t_token *current);

/* Error messages */
char				*get_validation_error_msg(t_cmd_valid_error error);
char				*get_syntax_error_msg(t_syntax_error error);
void				print_token_error(char *content);
void				print_paren_error(void);

/* Parentheses handling */
int					is_left_paren(t_token *token);
int					is_right_paren(t_token *token);
int					is_valid_after_subshell(t_token *token);
int					is_redirection(t_token *token);
t_ast_node			*handle_group_error(char *msg);
int					validate_subshell_command(t_ast_node *node);

#endif
