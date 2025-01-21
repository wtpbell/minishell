#include "../src/include/minishell.h"

int	error_msg (char *msg)
{
	char	*errno_msg;

	write(STDERR_FILENO, "minishell: ", 11);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	errno_msg = strerror(errno);
	if (errno_msg)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, errno_msg, ft_strlen(errno_msg));
	}
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

