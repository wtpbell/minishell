/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_process.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:45:18 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/16 22:07:27 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "common.h"
#include <sys/wait.h>

/*
	SIG_DFL (default handler for signal), informs the kernel that
	there is no user signal handler for the given signal, and that
	the kernel should take default action for it.
*/
void child(t_ast_node *node, t_env **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	printf("Executing command: %s\n", node->args[0]);
	fflush(stdout);

	char **env_arr = env_to_arr(*env);
	if (!env_arr)
	{
		perror("env_to_arr failed");
		exit(1);
	}

	execve(node->args[0], node->args, env_arr);
	perror("execve failed");  // If execve fails, this will be printed
	exit(127);  // Exit with 127 (command not found)
}



int	parent(t_ast_node *node)
{
	int	status_;

	wait(&status_);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else if (WIFSIGNALED(status_))
		status_ = WTERMSIG(status_) + 128;
	set_underscore(node->argc, node->args);
	set_exit_status(status_);
	signals_init();
	return (get_exit_status());
}
