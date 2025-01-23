#include "builtin.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void error(const char *word, const char *msg)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(SHELL_ERROR, STDERR_FILENO);
	if (msg)
	{
		ft_putstr_fd(word, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else
		perror(word);
	ft_putstr_fd(RESET, STDERR_FILENO);
	update_exit_status(1, NULL);
}
