/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 13:55:52 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/09 17:39:24 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include "minishell.h"
# include "parser.h"

/*
	ENVE: Local to the current shell session.
	EXPORT: Exported to child processes.
	BOTH: Both local and exported.
	SPECIAL: These may have a unique or internal role, 
	such as handling shell-specific behavior.
*/

typedef enum e_scope
{
	ENV = 1 << 0, // Environment only = VAR=value
	EXPORT = 1 << 1, // Exported variables = export VAR=value
	BOTH = 1 << 2, // Visible in both env and export
	SPECIAL = 1 << 3 // Special variables like "?" OLDWD, _, SHLVL
}	t_scope;

typedef struct s_env
{
	char				*key;
	char				*value;
	bool				hide;
	t_scope				scope;
	struct s_env		*prev;
	struct s_env		*next;
}	t_env;

/*env_init.c*/
t_env	*create_env(char *env);
t_env	*build_env(char **env);
t_env	**get_env_list(void);
void	setup_shlvl(t_env *new);
t_env	**get_env_list(void);

/*env_utils.c*/
t_env	*get_env(t_env *envs, const char *key);
char	*get_env_value(t_env *envs, const char *key);
void	add_env_var(t_env **env, char *key, char *value);

/*env_set.c*/
void	add_env(t_env **env, t_env *new);
void	set_env(t_env *envs, const char *key, const char *new_value);
void	set_underscore(int argc, char **args);
char	**env_to_arr(t_env *envs);
void	set_last(char **args, int argc);
int		set_underscore_error(t_ast_node *node, char *msg, int status_);
#endif
