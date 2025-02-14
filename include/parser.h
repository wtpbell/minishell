/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:46:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/14 11:28:28 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_last_redirs
{
	t_redirection	*in;
	t_redirection	*out;
	t_redirection	*heredoc;
	t_redirection	*append;
}	t_last_redirs;

typedef struct s_ast_node
{
	t_token_type		type;
	char				**args;
	int					argc;
	t_redirection		*redirections;
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

/* Main parsing functions */
t_ast_node			*parse(t_token *tokens);
t_ast_node			*parse_complete_bonus(t_token **token);
t_ast_node			*parse_logic(t_token **token);
t_ast_node			*parse_pipeline(t_token **token);
t_ast_node			*parse_command(t_token **token);
t_ast_node			*parse_group(t_token **token);
t_ast_node			*parse_redirection(t_token **token);
t_ast_node			*parse_pipe_sequence(t_token **token);

/* AST node manipulation */
t_ast_node			*create_ast_node(t_token_type type);
void				add_arg_to_node(t_ast_node *node, char *arg);
void				free_ast(t_ast_node *node);

/* Logic operation handling */
t_ast_node			*handle_logic_sequence(t_token **token, t_ast_node *left);
t_ast_node			*parse_command_sequence(t_token **token,
						t_token_type end_type);
t_ast_node			*handle_logic_operation(t_token **token,
						t_ast_node *left);
int					is_logic_operator(t_token *token);
t_ast_node			*create_logic_node(t_token **token);
t_ast_node			*handle_logic_error(void);
void				add_redirection(t_ast_node *node, t_token_type type,
						char *file);
t_ast_node			*create_pipe_node(t_ast_node *left, t_ast_node *right);
t_ast_node			*handle_redirection_in_pipe(t_ast_node *left,
						t_token **token);

/* Syntax validation */
t_cmd_valid_error	validate_command_syntax(t_ast_node *node);
t_cmd_valid_error	validate_redirection_syntax(t_redirection *redirs);
t_syntax_error		validate_syntax_tree(t_ast_node *root);
t_syntax_error		validate_redir_syntax(t_ast_node *node);
t_syntax_error		validate_subshell_syntax(t_ast_node *node);
int					validate_parentheses(t_token *tokens);
int					is_valid_command_name(const char *cmd);

/* Error messages */
char				*get_validation_error_msg(t_cmd_valid_error error);
char				*get_syntax_error_msg(t_syntax_error error);

/* AST optimization */
t_ast_node			*optimize_ast(t_ast_node *root);
t_ast_node			*remove_empty_nodes(t_ast_node *node);
t_redirection		*merge_redirections(t_redirection *redir);
t_ast_node			*optimize_pipeline(t_ast_node *node);

/* Parentheses handling */
int					is_left_paren(t_token *token);
int					is_right_paren(t_token *token);
int					is_valid_after_subshell(t_token *token);
int					is_redirection(t_token *token);
t_ast_node			*handle_group_error(char *msg);
int					validate_subshell_command(t_ast_node *node);

#endif
