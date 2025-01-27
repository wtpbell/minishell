/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 13:55:52 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/27 15:15:53 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include "minishell.h"

/*
	ENVE: Local to the current shell session.
	EXPORT: Exported to child processes.
	BOTH: Both local and exported.
	SPECIAL: These may have a unique or internal role, such as handling shell-specific behavior.
*/

typedef enum	e_scope
{
	ENVE = 1 << 0,   // Environment only = VAR=value
	EXPORT = 1 << 1, // Exported variables = export VAR=value
	BOTH = 1 << 2,   // Visible in both env and export
	SPECIAL = 1 << 3 // Special variables like "?" OLDWD, _, SHLVL
} t_scope;

typedef struct	s_env
{
	char		*key;
	char		*value;
	bool		hide; // hide from env, handle "unset" without removing them
	t_scope		scope;
	t_env		*prev;
	t_env		*next;
}	t_env;


/*env_init.c*/
t_env	*creat_env(char *env);
t_env	*build_env(char **env);
t_env	**get_env_list(void);


/*env_utils.c*/
void	add_env(t_env **env, t_env *new);
void	setup_shlvl(t_env *new);
t_env	*get_env(t_env *envs, const char *key);

#endif
