/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 12:13:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/14 09:53:56 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "common.h"
# include "minishell.h"
# include "parser.h"

typedef struct s_dir_info
{
	char	***matches;
	int		*count;
	int		*capacity;
	char	*pattern;
}	t_dir_info;

typedef struct s_copy_params
{
	char	**new_args;
	char	**node_args;
	int		arg_idx;
	char	**matches;
	int		match_count;
	int		node_argc;
}	t_copy_params;

typedef struct s_expansion_state
{
	t_quote_type	current_quote;
	int				in_double_quotes;
}	t_expansion_state;

void	expander(t_ast_node *node, t_env **env_list);
int		should_skip_expansion(t_ast_node *node, int i, int dollar_exp);
int		contains_expandable_dollar(const char *str, t_ast_node *node, int i);
void	handle_arg_expansion(t_ast_node *node, t_env **env_list,
			t_tokenizer *tokenizer, int i);
char	*extract_var_name_expander(char *arg, int *var_len);
void	handle_exit_status_expansion(t_ast_node *node, int i);
char	*process_dollar(const char *str, int *i, t_env *env_list,
			t_quote_type quote_type);
char	*handle_dollar_sign(const char *arg, int *i,
			char *result, t_quote_type current_quote);
char	*handle_regular_char(const char *arg, int *i, char *result);
char	*handle_escape_char(const char *arg, int *i,
			char *result, t_quote_type current_quote);
char	*handle_single_quote_dollar(const char *arg, int *i,
			char *result, t_quote_type current_quote);
char	*handle_exit_status(int *i, char *result);
char	*process_exit_status_in_dquotes(const char *arg, int *i,
			char *result);
void	handle_quote_char(char c, t_quote_type *current_quote);
char	*process_string_char(char c, char *result);
char	*process_expansion(const char *arg, int *i,
			char *result, t_quote_type current_quote);
char	*process_escapes_and_expansion(const char *arg, int *i,
			char *result, t_quote_type *current_quote);
int		is_full_exit_status_pattern(const char *arg, int i);
char	*handle_expansion(t_tokenizer *tokenizer, const char *arg);
void	copy_args_range(char **dest, char **source, int range[2],
			int *dest_idx);
void	copy_matches(char **dest, char **matches, int match_count,
			int *dest_idx);
void	free_matches(char **matches, int match_count);
void	process_wildcard_arg(t_ast_node *node, int i);
void	expand_wildcards(t_ast_node *node);
void	process_mixed_wildcard(t_ast_node *node, int i);
int		is_mixed_quote_wildcard(const char *str, t_quote_type quote_type);
bool	replace_wildcard_arg(t_ast_node *node, int arg_idx, char **matches,
			int match_count);
char	**init_matches_array(int initial_capacity);
int		should_include_file(const char *filename, const char *pattern);
char	**grow_matches_array(char **matches, int *capacity);
void	cleanup_matches(char **matches, int count);
int		add_matching_file(char ***matches, int *count, int *capacity,
			const char *filename);
int		process_dir_entries(DIR *dir, t_dir_info *info);
char	**get_matching_files(const char *pattern, int *num_matches);
char	*expand_heredoc_line(char *line, t_env *env_list);
void	expand_redir_wildcards(t_redir *redir);
char	*join_and_free(char *s1, char *s2);
char	*join_matches_with_spaces(char **matches, int match_count);
void	handle_env_dollar_expansion(t_ast_node *node, t_env **env_list,
			int i, int *had_expansion);
void	handle_dollar_expansion(t_ast_node *node, t_tokenizer *tokenizer,
			int i, int *had_expansion);
void	handle_wildcard_with_expansion(t_ast_node *node, int i);
void	expand_env_var(t_ast_node *node, t_env **env_list, int i);
void	handle_dollar_in_string(t_ast_node *node, t_tokenizer *tokenizer,
			int i);
void	handle_wildcard_expansion(t_ast_node *node, int i);
char	*join_matches_with_spaces(char **matches, int match_count);
char	*process_wildcard_in_variable(char *value);
int		should_repeat_expansion(t_ast_node *node, int i,
			int had_env_expansion);
void	process_wildcard(t_ast_node *node, int i, int had_env_expansion);
int		process_env_expansion(t_ast_node *node, t_env **env_list,
			t_tokenizer *tokenizer, int i);
#endif
