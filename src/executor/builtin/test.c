#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "executor.h"


char *mock_env[] = {
	"PATH=/usr/bin",
	"HOME=/home/user",
	"SHELL=minishell",
	NULL
};

// Helper function to create a `t_exec` struct
t_exec *create_cmd(char **args, char ***env_ptr, int *exit_code)
{
	t_exec *cmd = malloc(sizeof(t_exec));
	if (!cmd)
		return NULL;
	cmd->argv = args;
	cmd->env_ptr = env_ptr;
	cmd->exitcode = exit_code;
	cmd->next = NULL;
	return (cmd);
}

int main()
{
	int exit_code = 0;
	char **env_ptr = mock_env;

	// Test the "env" built-in
	printf("=== Testing builtin_env ===\n");
	char *env_args[] = {"env", NULL};
	t_exec *env_cmd = create_cmd(env_args, &env_ptr, &exit_code);
	builtin_env(env_cmd);
	printf("Exit code: %d\n", exit_code);

	// Test the "echo" built-in
	printf("\n=== Testing builtin_echo ===\n");
	char *echo_args[] = {"echo", "-n", "Hello,", "world!", NULL};
	t_exec *echo_cmd = create_cmd(echo_args, &env_ptr, &exit_code);
	builtin_echo(echo_cmd);
	printf("\nExit code: %d\n", exit_code);

	// Test the "exit" built-in
	printf("\n=== Testing builtin_exit ===\n");
	char *exit_args[] = {"exit", "42", NULL};
	t_exec *exit_exec = create_cmd(exit_args, &env_ptr, &exit_code);
	builtin_exit(exit_exec);
	printf("Exit code: %d\n", exit_code);

	// Cleanup
	free(env_cmd);
	free(echo_cmd);
	free(exit_exec);

	return (0);
}
