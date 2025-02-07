#include "builtin.h"
#include "minishell.h"
#include "executor.h"
#include <stdio.h>
#include <unistd.h>

void error(char *word, char *msg)
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
	{
		ft_putstr_fd(word, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO); 
	}
	ft_putstr_fd(RESET, STDERR_FILENO);
	set_exit_status(EXIT_FAILURE);
}
