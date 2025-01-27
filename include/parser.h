/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:46:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/27 09:20:30 by spyun         ########   odam.nl         */
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

typedef struct s_ast_node
{
	t_token_type		type;
	char				**args;
	int					argc;
	t_redirection		*redirections;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*parse(t_token *tokens);
void		free_ast(t_ast_node *node);
t_ast_node	*create_ast_node(t_token_type type);
void		add_arg_to_node(t_ast_node *node, char *arg);
t_ast_node	*parse_pipeline(t_token **token);

t_ast_node	*parse_command(t_token **token);
t_ast_node	*create_logic_node(t_token **token);
t_ast_node	*handle_logic_error(void);
t_ast_node	*process_logic_operator(t_token **token,
				t_ast_node *left, t_ast_node *logic_node);
t_ast_node	*handle_logic_sequence(t_token **token, t_ast_node *left);
t_ast_node	*parse_logic(t_token **token);
t_ast_node	*parse_complete_bonus(t_token **token);
t_ast_node	*parse_group(t_token **token);
t_ast_node	*parse_redirection(t_token **token);
#endif
