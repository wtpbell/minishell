/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 12:13:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/26 14:55:37 by spyun         ########   odam.nl         */
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

void	expander(t_ast_node *node, t_env **env_list);
int		should_skip_expansion(t_ast_node *node, int i, int dollar_exp);

void	handle_arg_expansion(t_ast_node *node, t_env **env_list,
			t_tokenizer *tokenizer, int i);

char	*process_dollar(const char *str, int *i, t_env *env_list,
			t_quote_type quote_type);

char	*handle_expansion(t_tokenizer *tokenizer, const char *arg);

void	copy_args_range(char **dest, char **source, int range[2],
			int *dest_idx);
void	copy_matches(char **dest, char **matches, int match_count,
			int *dest_idx);
void	free_matches(char **matches, int match_count);
void	expand_wildcards(t_ast_node *node);

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
#endif
