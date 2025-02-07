/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:46:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/07 14:46:56 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"
# include "env.h"

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
	t_env				**env;
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
}	t_syntax_error;

t_ast_node			*parse(t_token *tokens);
void				free_ast(t_ast_node *node);
t_ast_node			*create_ast_node(t_token_type type);
void				add_arg_to_node(t_ast_node *node, char *arg);
t_ast_node			*parse_pipeline(t_token **token);

t_ast_node			*parse_command(t_token **token);
t_ast_node			*create_logic_node(t_token **token);
t_ast_node			*handle_logic_error(void);
t_ast_node			*process_logic_operator(t_token **token,
						t_ast_node *left, t_ast_node *logic_node);
t_ast_node			*handle_logic_sequence(t_token **token, t_ast_node *left);
t_ast_node			*parse_logic(t_token **token);
t_ast_node			*parse_complete_bonus(t_token **token);
t_ast_node			*parse_group(t_token **token);
t_ast_node			*parse_redirection(t_token **token);

t_cmd_valid_error	validate_command_syntax(t_ast_node *node);
t_cmd_valid_error	validate_redirection_syntax(t_redirection *redirs);
char				*get_validation_error_msg(t_cmd_valid_error error);
int					is_valid_command_name(const char *cmd);

t_syntax_error		validate_redir_syntax(t_ast_node *node);
t_syntax_error		validate_syntax_tree(t_ast_node *root);

char				*get_validation_error_msg(t_cmd_valid_error error);
char				*get_syntax_error_msg(t_syntax_error error);

t_ast_node			*optimize_ast(t_ast_node *root);
t_ast_node			*remove_empty_nodes(t_ast_node *node);
t_redirection		*merge_redirections(t_redirection *redir);
t_ast_node			*optimize_pipeline(t_ast_node *node);

#endif
